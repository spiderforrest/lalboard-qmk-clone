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

#pragma once

#include "quantum.h"

//Layout for svalboard v0
//1 2 3 4 5
//S E D N W
//Both Thumbs (same as lalboard_v2)
//OL OU D IL MODE DOUBLE
#define LAYOUT( \
    r1d, r1n, r1e, r1s, r1w, \
    r2d, r2n, r2e, r2s, r2w, \
    r3d, r3n, r3e, r3s, r3w, \
    r4d, r4n, r4e, r4s, r4w, \
    l1d, l1n, l1e, l1s, l1w, \
    l2d, l2n, l2e, l2s, l2w, \
    l3d, l3n, l3e, l3s, l3w, \
    l4d, l4n, l4e, l4s, l4w, \
    rtd, rti, rtu, rtuo, rtlo, rtdd, \
    ltd, lti, ltu, ltuo, ltlo, ltdd) \
{ \
    {rtlo,rtuo,rtd, rti, rtu, rtdd}, \
    {r1s, r1e, r1d, r1n, r1w, KC_NO}, \
    {r2s, r2e, r2d, r2n, r2w, KC_NO}, \
    {r3s, r3e, r3d, r3n, r3w, KC_NO}, \
    {r4s, r4e, r4d, r4n, r4w, KC_NO}, \
     \
    {ltlo,ltuo,ltd, lti, ltu, ltdd}, \
    {l1s, l1e, l1d, l1n, l1w, KC_NO}, \
    {l2s, l2e, l2d, l2n, l2w, KC_NO}, \
    {l3s, l3e, l3d, l3n, l3w, KC_NO}, \
    {l4s, l4e, l4d, l4n, l4w, KC_NO}, \
}

#define SPLIT_TRANSPORT_UART_NUM 1
#define SPLIT_TRANSPORT_UART_RX 12
#define SPLIT_TRANSPORT_UART_RX_BUFFER_SIZE 256
#define SPLIT_TRANSPORT_UART_TX 13
#define SPLIT_TRANSPORT_UART_TX_BUFFER_SIZE 256
