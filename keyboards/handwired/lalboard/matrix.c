/* Copyright 2021 Ben Gruver <jesusfreke@jesusfreke.com>
 *
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS
 * IN THE SOFTWARE.
 */

#include <stdint.h>
#include <stdbool.h>

#include "lalboard.h"
#include "config.h"

#include "action.h"
#include "gpio.h"
#include "keyboard.h"
#include "matrix.h"
#include "print.h"

#include "driver/uart.h"
#include "esp_err.h"

static matrix_row_t current_matrix[MATRIX_ROWS];

static const pin_t row_pins[LOCAL_MATRIX_ROWS] = MATRIX_ROW_PINS;
static const pin_t col_pins[MATRIX_COLS] = MATRIX_COL_PINS;
static const uint8_t col_pushed_states[MATRIX_COLS] = MATRIX_COL_PUSHED_STATES;
static const uint8_t col_pushed_states_thumbs[MATRIX_COLS] = MATRIX_COL_PUSHED_STATES_THUMBS;

matrix_row_t matrix_get_row(uint8_t row) {
    return current_matrix[row];
}

uint8_t get_first_local_row(void) {
    return is_keyboard_left() ? (LOCAL_MATRIX_ROWS) : 0;
}

uint8_t get_first_remote_row(void) {
    return is_keyboard_left() ? 0 : (LOCAL_MATRIX_ROWS);
}

void matrix_print(void) {
  print("\nr/c ");
  for (uint8_t col = 0; col < MATRIX_COLS; col++) {
      print_hex8(col);
  }
  print("\n");

  for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
    print_hex8(row);
    print(": ");

    // esp-idf's printf doesn't seem to support the %b specifier, so we'll just
    // print out the bits manually

    // c why
    //matrix_row_t row_value = current_matrix[row];
    for (uint8_t col_bit = 1 << (MATRIX_COLS - 1); col_bit != 0; col_bit >>= 1) {
        print((current_matrix[row] | col_bit) ? "1" : "0");
    }

    print("\n");
  }
}

__attribute__((weak)) void matrix_init_kb(void) { matrix_init_user(); }

__attribute__((weak)) void matrix_init_user(void) {}

void matrix_init(void) {
    for (int row = 0; row < sizeof(row_pins)/sizeof(pin_t); row++) {
        setPinOutput(row_pins[row]);
        writePin(row_pins[row], 0);
    }

    for (int col = 0; col < sizeof(col_pins)/sizeof(pin_t); col++) {
        setPinInput(col_pins[col]);
    }
    setPinInputHigh(col_pins[5]); // use pullup for tact switches (the opamps for the other keys drive the lines directly)

    matrix_init_quantum();
}

__attribute__((weak)) void matrix_scan_kb(void) { matrix_scan_user(); }

__attribute__((weak)) void matrix_scan_user(void) {}


matrix_row_t read_row(bool thumbs) {
    matrix_row_t row = 0;

    for (int col = 0; col < MATRIX_COLS; col++) {
        int col_pin = col_pins[col];
        if (thumbs == true){
            if (readPin(col_pin) == col_pushed_states_thumbs[col]) {
                row |= 1 << col;
            }
        }
        else {
            if (readPin(col_pin) == col_pushed_states[col]) {
                row |= 1 << col;
            }
        }
    }

    return row;
}

bool read_remote_matrix(void) {
    bool changed = false;

    uint8_t buf[32];
    int bytes_read = uart_read_bytes(SPLIT_TRANSPORT_UART_NUM, buf, sizeof(buf), 0);

    uint8_t first_remote_row = get_first_remote_row();
    for (int i = 0; i < bytes_read; i++) {
        uint8_t row_data = buf[i];
        uint8_t remote_row_index = (row_data >> 5);
        matrix_row_t new_remote_row = row_data & 0b00011111;

        uint8_t global_row_index = first_remote_row + remote_row_index;
        changed |= new_remote_row != current_matrix[global_row_index];
        current_matrix[global_row_index] = new_remote_row;
    }

    return changed;
}

void send_local_matrix(void) {
    uint8_t buf[LOCAL_MATRIX_ROWS];
    int first_local_row = get_first_local_row();
    for (int local_row_index = 0; local_row_index < LOCAL_MATRIX_ROWS; local_row_index++) {
        int global_row_index = first_local_row + local_row_index;
        buf[local_row_index] = (local_row_index << 5) | (current_matrix[global_row_index] & 0b00011111);
    }

    size_t bytes_written = uart_write_bytes(SPLIT_TRANSPORT_UART_NUM, buf, sizeof(buf));
    if (bytes_written != sizeof(buf)) {
        printf("Wrote an unexpected number of bytes to the uart: %d\n", bytes_written);
    }
}

uint8_t matrix_scan(void) {
    bool changed = false;
    bool use_thumb_mask = false;

    int first_local_row = get_first_local_row();

    for (int local_row = 0; local_row < LOCAL_MATRIX_ROWS; local_row++) {
        pin_t row_pin = row_pins[local_row];
        writePin(row_pin, 1);
        wait_us(40);

        uint8_t global_row = first_local_row + local_row;

        use_thumb_mask = (local_row == 0);                          // only use the Thumbs mask for row 0 local -- this is also row 5 of 10 remote
        matrix_row_t new_row = read_row(use_thumb_mask);    //

        changed |= new_row != current_matrix[global_row];
        current_matrix[global_row] = new_row;
        writePin(row_pin, 0);

        wait_us(40);
    }

    if (is_keyboard_master()) {
        changed |= read_remote_matrix();
    } else if (changed) {
        send_local_matrix();
    }

    matrix_scan_quantum();
    return changed;
}

void matrix_power_down(void) {
    for (int row = 0; row < LOCAL_MATRIX_ROWS; row++) {
        int row_pin = row_pins[row];
        writePin(row_pin, 0);
        wait_us(40);
    }
}
