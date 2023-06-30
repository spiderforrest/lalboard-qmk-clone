/* This is the c configuration file for the keymap

Copyright 2023 Spider Forrest <qmk@spood.org>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/


#define FORCE_NKRO

#pragma once

// The column with the "down" keys on both the normal and thumb clusters
// is inverted.  This should be true on all units manufactured after 5/31/2023
// and is on mine :)
#undef MATRIX_COL_PUSHED_STATES
#define MATRIX_COL_PUSHED_STATES { 0, 0, 1, 0, 0, 0 };


// Mouse key speed and acceleration
#undef MOUSEKEY_DELAY
#define MOUSEKEY_DELAY              0
#undef MOUSEKEY_INTERVAL
#define MOUSEKEY_INTERVAL           16
#undef MOUSEKEY_MAX_SPEED
#define MOUSEKEY_MAX_SPEED          6
#undef MOUSEKEY_TIME_TO_MAX
#define MOUSEKEY_TIME_TO_MAX        64
#undef MOUSEKEY_MOVE_DELTA
#define MOUSEKEY_MOVE_DELTA         8

#undef MOUSEKEY_WHEEL_DELAY
#define MOUSEKEY_WHEEL_DELAY        0
#undef MOUSEKEY_WHEEL_INTERVAL
#define MOUSEKEY_WHEEL_INTERVAL     80

// misc
#define COMBO_TERM 45
// #define SPLIT_LAYER_STATE_ENABLE //share layer with other hand

// space optimization
#undef LOCKING_SUPPORT_ENABLE		        // disabling lock key support
#undef LOCKING_RESYNC_ENABLE
#define LAYER_STATE_16BIT		            // total 16 layers
#define EXTRA_SHORT_COMBOS

// layout override
// rows are most effort to least
// ( top to bottom: out, in, up, down, x)
// ( the last letter is cardinal direction, with d for what i call x )
// columns are left to right fingers
// thumb clusters are
// uh
// just check keymap.c
#define VISUAL_LAYOUT( \
 l4w, l3w, l2w, l1w, r1e, r2e, r3e, r4e,    \
 l4e, l3e, l2e, l1e, r1w, r2w, r3w, r4w,    \
 l4n, l3n, l2n, l1n, r1n, r2n, r3n, r4n,    \
 l4s, l3s, l2s, l1s, r1s, r2s, r3s, r4s,    \
 l4d, l3d, l2d, l1d, r1d, r2d, r3d, r4d,    \
                                            \
 ltu,      ltuo,         rtuo,      rtu,    \
 lti, ltd, ltlo,         rtlo, rtd, rti,    \
      ltdd,                    rtdd         \
        ) \
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
