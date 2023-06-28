/* Copyright 2021 Ben Gruver <jesusfreke@jesusfreke.com> {{{
 * 2023 Spider Forrest <lalboard-qmk-clone@spood.org>
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
}}} */

/*  {{{ keyboard effort calc config
 *  https://colemakmods.github.io/mod-dh/analyze.html


            left     right
          ┌───────┐ ┌───────┐
          x n e s w x n e s w
         ╔╬═╬═╬═╬═╬═╬═╬═╬═╬═╬═╗
         ║a b c d e f g h i j═╬═ index
         ║k l m n o p q r s t═╬═ middle
         ║u v w x y z . , ; /═╬═ ring
         ║1 2 3 4 5 6 7 8 9 0═╬═ pinky
         ╚════════════════════╝

0 = esc
1, 2 = probably (, )
═══════╦═══════════════════════╦═══════
       ║ the ../default keymap ║
       ╚═══════════════════════╝

          a q [ z 3 n l = m h
          r w b x 0 e u ; , k
          s f d c ` i y 4 . j
          t p g v ' o 5 \ / ]

═══════╦════════════════════════╦═══════
       ║ this was colemak, once ║
       ╚════════════════════════╝

          a f g p , n l 0 h .
          r c b d 1 e u / k '
          s x z w 2 i y ; m -
          t q | v [ o \ ] j =

═══════╦════════════════════════╦═══════
       ║ the config for weights ║
 ╔═════╩════════════════════════╩═════╗
 ║ it's worth noting that the weights ║
 ║ are tuned to my fingers and I have ║
 ║ quirks like bad pinkies-esp north, ║
 ║ so you should probably change the  ║
 ║ effort skew values for yourself.   ║
 ╚════════════════════════════════════╝

 effort: 4
1.0 1.4 2.3 1.2 2.6 1.0 1.4 2.6 1.2 2.3
1.1 1.6 2.9 1.3 3.0 1.1 1.6 3.0 1.3 2.9
1.3 2.0 3.2 1.6 3.7 1.3 2.0 3.7 1.6 3.2
1.6 3.8 3.4 2.8 4.2 1.6 3.8 4.2 2.8 3.4

penalties:
 2.5  3.0  4.0  #same-finger
 0.5  1.0  1.5  #pinky-ring
 0.1  0.2  0.3  #ring-middle
-0.2 -0.1  0.0  #middle-index

fingers: 4
0 0 0 0 0 6 6 6 6 6
1 1 1 1 1 7 7 7 7 7
2 2 2 2 2 8 8 8 8 8
3 3 3 3 3 9 9 9 9 9

type:
matrix_simple

═══════════════════════════════════════
}}} */

// {{{ layer template
//    [LAYER] = LAYOUT(
//        // Center       North           East            South           West
//        _______,        _______,        _______,        _______,        _______,                    // Right Index
//        _______,        _______,        _______,        _______,        _______,                    // Right Middle
//        _______,        _______,        _______,        _______,        _______,                    // Right Ring
//        _______,        _______,        _______,        _______,        _______,                    // Right Pinky
//
//        // Center       North           East            South           West
//        _______,        _______,        _______,        _______,        _______,                    // Left Pinky
//        _______,        _______,        _______,        _______,        _______,                    // Left Ring
//        _______,        _______,        _______,        _______,        _______,                    // Left Middle
//        _______,        _______,        _______,        _______,        _______,                    // Left Index
//
//        // Down         Inner           Upper           Outer Upper     Outer Lower     Follow Through
//        _______,        _______,        _______,        _______,        _______,        _______,    // Right Thumb
//        _______,        _______,        _______,        _______,        _______,        _______     // Left Thumb
//    )
// }}}

#include QMK_KEYBOARD_H

#include <stdbool.h>
#include <stdint.h>

enum my_keycodes {
    _ = SAFE_RANGE,
};

enum layer {
    DANSEN,
    SYMOUSE,
};

#define KC_RIGHT_CURLY KC_RIGHT_CURLY_BRACE
#define KC_L_CRLY KC_LEFT_CURLY_BRACE


/* Declared weak so that it can easily be overridden. */
__attribute__((weak)) const uint16_t PROGMEM keymaps[NUM_LAYERS][MATRIX_ROWS][MATRIX_COLS] = {
    [DANSEN] = LAYOUT(
        // Center       North           East            South           West
        KC_N,           KC_L,           KC_ESC,         KC_H,           KC_DOT,                    // Right Index
        KC_E,           KC_U,           KC_SLASH,       KC_K,           KC_QUOTE,                  // Right Middle
        KC_I,           KC_Y,           KC_SCOLON,      KC_M,           KC_MINUS,                  // Right Ring
        KC_O,           KC_BSLASH,      KC_RBRC,        KC_J,           KC_LEFT,                   // Right Pinky

        // Center       North           East            South           West
        KC_T,           KC_Q,           KC_PIPE,        KC_V,           KC_LBRC,                   // Left Pinky
        KC_S,           KC_X,           KC_V,           KC_W,           _______, // no idea tbh    // Left Ring
        KC_R,           KC_C,           KC_B,           KC_D,           _______, // maybe util osl // Left Middle
        KC_A,           KC_F,           KC_G,           KC_P,           KC_COMMA,                  // Left Index


        // Down         Inner           Upper           Outer Upper     Outer Lower     Follow Through
        KC_TAB,         KC_BSPACE       layer,          DC_DELE,        KC_LALT,        _______,   // Right Thumb
        KC_ENTER,       KC_SPACE,       layer,          KC_TAB,         KC_LCTRL,       _______    // Left Thumb
    ),
    [DART] = LAYOUT(
        // Center       North           East            South           West
        // arrow keys   nav cluster     audio/media     mouse move      mouse wheel
        KC_LEFT,        KC_HOME,        KC_MUTE,        KC_MS_L,        KC_WH_L,                    // Right Index
        KC_DOWN,        KC_PGDN,        KC_VOLD,        KC_MS_D,        KC_WH_U,                    // Right Middle
        KC_UP,          KC_PGUP,        KC_VOLU,        KC_MS_U,        KC_WH_D,                    // Right Ring
        KC_RIGHT,       KC_END,         KC_F22,         KC_MS_R,        KC_WH_R,                    // Right Pinky

        // Center       North           East            South           West
        _______,        _______,        _______,        _______,        _______,                    // Left Pinky
        KC_7,           KC_4,           _______,        KC_1,           _______,                    // Left Ring
        KC_8,           KC_5,           _______,        KC_2,           _______,                    // Left Middle
        KC_9,           KC_6,           KC_0,           KC_3,           _______,                    // Left Index

        // Down         Inner           Upper           Outer Upper     Outer Lower     Follow Through
        _______,        _______,        _______,        _______,        _______,        _______,    // Right Thumb
        _______,        _______,        _______,        _______,        _______,        _______     // Left Thumb
    )
};



// vim:foldmethod=marker
