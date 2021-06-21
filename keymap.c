/* Copyright 2015-2017 Jack Humbert
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include QMK_KEYBOARD_H
#include "muse.h"

enum preonic_layers {
  _QWERTY,
  _LOWER
};

enum preonic_keycodes {
  QWERTY = SAFE_RANGE,
  LOWER,
  MACRO1
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* Qwerty
 * ,-----------------------------------------------------------------------------------.
 * | Esc  |   1  |   2  |   3  |   4  |   5  |   6  |   7  |   8  |   9  |   0  | Bksp |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Tab  |   Q  |   W  |   E  |   R  |   T  |   Y  |   U  |   I  |   O  |   P  | Del  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | |\   |   A  |   S  |   D  |   F  |   G  |   H  |   J  |   K  |   L  |   ;  |  "   |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | Shift|   Z  |   X  |   C  |   V  |   B  |   N  |   M  |   ,  |   .  |   /  |Enter |
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * | Ctrl | Home | End  | ALT  |Lower |    Space    | -    | =    | [    |  ]   | `    |
 * `-----------------------------------------------------------------------------------'
 */
[_QWERTY] = LAYOUT_preonic_grid(
  KC_ESC,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC,
  KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_DEL,
  KC_BSLS, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
  KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_ENT,
  KC_LCTL, KC_HOME, KC_END, KC_LALT, LOWER,   KC_SPC,  KC_SPC,  KC_MINS,   KC_EQL, KC_LBRC, KC_RBRC,   KC_GRV
),

/* Lower
 * ,-----------------------------------------------------------------------------------.
 * |  F1  |  F2  |  F3  |  F4  |  F5  |  F6  |  F7  |  F8  |  F9  | F10  | F11  | F12  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * |      |      |  UP  |      |      |      |      |  RGB |  RGB |  RGB |  RGB | RGB  |
 * |------+------+------+------+------+-------------+------+------+------+------+------|
 * | PRNT | LEFT | DOWN | RIGHT|      |      |      |  RGB |  RGB |  RGB |  RGB | RGB  |
 * |------+------+------+------+------+------|------+------+------+------+------+------|
 * | CAPS |      |      |      |      |      |      |      |      | PREV | NEXT |MACRO1|
 * |------+------+------+------+------+------+------+------+------+------+------+------|
 * |  ^   |  ^   | WIN  |      |  ^   |             |RESET |      | Vol- | Vol+ | Play |
 * `-----------------------------------------------------------------------------------'
 */
[_LOWER] = LAYOUT_preonic_grid(
  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6, KC_F7, KC_F8,   KC_F9,   KC_F10,  KC_F11,   KC_F12,
  KC_NO,   KC_NO,   KC_UP,   KC_NO,   KC_NO,   KC_NO, KC_NO, RGB_SAI, RGB_HUI, RGB_VAI, RGB_MOD,  RGB_TOG,
  KC_PSCR, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO, KC_NO, RGB_SAD, RGB_HUD, RGB_VAD, RGB_RMOD, RGB_M_P,
  KC_CAPS, KC_NO,   KC_NO,   KC_NO,   KC_NO,   KC_NO, KC_NO, KC_NO,   KC_NO,   KC_MPRV, KC_MNXT,  MACRO1,
  KC_TRNS, KC_TRNS, KC_LGUI, KC_NO,   KC_TRNS, KC_NO, KC_NO, RESET,   KC_NO,   KC_VOLD, KC_VOLU,  KC_MPLY
)

};

bool execute_macro1 = false;

void matrix_init_user(void) { }

void matrix_scan_user(void) {
  if (execute_macro1) {
    tap_code(KC_MS_UP);
    tap_code(KC_MS_DOWN);
    tap_code(KC_MS_LEFT);
    tap_code(KC_MS_RIGHT);
    tap_code(KC_MS_WH_UP);
    tap_code(KC_MS_WH_DOWN);
  }
  else { }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
      case QWERTY:
        if (record->event.pressed) {
          set_single_persistent_default_layer(_QWERTY);
        }
        return false;
        break;
      case LOWER:
        if (record->event.pressed) {
          layer_on(_LOWER);
        } else {
          layer_off(_LOWER);
        }
        return false;
        break;
      case MACRO1:
        if (record->event.pressed) {
          execute_macro1 = !execute_macro1;
        }
        return false;
        break;
      }
    return true;
};


