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

/* {{{ layer template

    ), [LAYER] = VISUAL_LAYOUT(
    // pinky    ring        middle      index       index       middle      ring        pinky
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    // out
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    // in
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    // up
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    // down
    _______,    _______,    _______,    _______,    _______,    _______,    _______,    _______,    // x

                // inner    down        outer       outer       down        inner
                _______,                _______,    _______,                _______,                // upper
                _______,    _______,    _______,    _______,    _______,    _______,                // lower
                            _______,                            _______                             // follow through


}}} */

// {{{
#include QMK_KEYBOARD_H

#include <stdbool.h>
#include <stdint.h>

/* enum custom_keycodes { */
/*     _ = SAFE_RANGE, */
/* }; */

enum layer {
    DANSEN,
    DART,
    LAYER_COUNT
};


// shorthands
#define KC_ KC_NO
// }}}


/* Declared weak so that it can easily be overridden. */
__attribute__((weak)) const uint16_t PROGMEM keymaps[LAYER_COUNT][MATRIX_ROWS][MATRIX_COLS] = {

    [DANSEN] = VISUAL_LAYOUT( // {{{
    // pinky    ring        middle      index       index       middle      ring        pinky
    KC_BSLS,    KC_GRV,     KC_LCTL,    KC_B,       KC_M,       KC_LALT,    KC_EQL,     KC_QUOT,    // out
    KC_ESC,     KC_LBRC,    KC_DOT,     KC_G,       KC_K,       KC_COMM,    KC_RBRC,    KC_MINS,    // in
    KC_Z,       KC_W,       KC_F,       KC_P,       KC_L,       KC_U,       KC_Y,       KC_SCLN,    // up
    KC_Q,       KC_X,       KC_C,       KC_D,       KC_H,       KC_J,       KC_V,       KC_SLSH,    // down
    KC_A,       KC_R,       KC_S,       KC_T,       KC_N,       KC_E,       KC_I,       KC_O,       // x

                // inner    down        outer       outer       down        inner
                MO(DART),               KC_LALT,    KC_LCTL,                KC_DEL,                 // upper
                KC_LSFT,    KC_SPC,     KC_TAB,     KC_ENT,     KC_BSPC,    KC_LGUI,                // lower
                            KC_,                                KC_                                 // follow through
    ), // }}}

    [DART] = VISUAL_LAYOUT( // {{{
    // pinky    ring        middle      index       index       middle      ring        pinky
    _______,    _______,    _______,    _______,    KC_MUTE,    KC_VOLD,    KC_VOLU,    KC_F22,     // out
    _______,    _______,    KC_PIPE,    KC_0,       KC_WH_L,    KC_WH_U,    KC_WH_D,    KC_WH_R,    // in
    _______,    KC_7,       KC_8,       KC_9,       KC_HOME,    KC_PGDN,    KC_PGUP,    KC_END,     // up
    _______,    KC_1,       KC_2,       KC_3,       KC_MS_L,    KC_MS_D,    KC_MS_U,    KC_MS_R,    // down
    KC_LSFT,    KC_4,       KC_5,       KC_6,       KC_LEFT,    KC_DOWN,    KC_UP,      KC_RIGHT,   // x

                // inner    down        outer       outer       down        inner
                _______,                _______,    _______,                KC_BTN3,                // upper
                _______,    _______,    _______,    _______,    _______,    KB_BTN1,                // lower
                            _______,                            _______                             // follow through

    ) // }}}

};



// vim:foldmethod=marker
