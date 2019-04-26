/* Copyright 2019 Jakub Darowski jakub@darowski.dev @jdarowski
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

enum layers {
  _BASE = 0,
  _FN1,
  _FN2,
};

// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
  QMKBEST = SAFE_RANGE,
  QMKURL
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BASE] = LAYOUT_ortho_4x4(
    KC_PGUP,  KC_HOME,  KC_UP,    KC_END , \
    KC_PGDN,  KC_LEFT,  KC_DOWN,  KC_RGHT, \
    MO(_FN2), KC_VOLU,  KC_MPLY,  KC_MPRV, \
    MO(_FN1), KC_VOLD,  KC_MUTE,  KC_MNXT  \
  ),
  [_FN1] = LAYOUT_ortho_4x4(
    KC_ESC,   KC_P7,    KC_P8,    KC_P9,   \
    KC_TAB,   KC_P4,    KC_P5,    KC_P6,   \
    KC_ENT,   KC_P1,    KC_P2,    KC_P3,   \
    _______,  KC_P0,    KC_P0,    KC_DOT   \
  ),
  [_FN2] = LAYOUT_ortho_4x4(
    RGB_TOG,  RGB_HUI,  RGB_SAI,  RGB_VAI, \
    RGB_MOD,  RGB_HUD,  RGB_SAD,  RGB_VAD, \
    _______,  _______,  _______,  RESET,   \
    BL_STEP,  _______,  QMKBEST,  QMKURL   \
  )

};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
    case QMKBEST:
      if (record->event.pressed) {
        // when keycode QMKBEST is pressed
        SEND_STRING("QMK is the best thing ever!");
      } else {
        // when keycode QMKBEST is released
      }
      break;
    case QMKURL:
      if (record->event.pressed) {
        // when keycode QMKURL is pressed
        SEND_STRING("https://qmk.fm/" SS_TAP(X_ENTER));
      } else {
        // when keycode QMKURL is released
      }
      break;
  }
  return true;
}

uint8_t last_layer = 1 << 7;

uint32_t layer_state_set_user(uint32_t state) {
  uint8_t layer = biton32(state);

  if (layer == last_layer) {
    return state;
  }

  last_layer = layer;

  switch (layer) {
    case _BASE:
      rgblight_sethsv_noeeprom(HSV_WHITE);
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      break;
    case _FN1:
      rgblight_sethsv_noeeprom(HSV_RED);
      rgblight_mode_noeeprom(RGBLIGHT_MODE_SNAKE + 3);
      break;
    case _FN2:
      rgblight_sethsv_noeeprom(HSV_BLUE);
      rgblight_mode_noeeprom(RGBLIGHT_MODE_SNAKE + 3);
      break;
    default:
      rgblight_sethsv_noeeprom(HSV_PINK);
      rgblight_mode_noeeprom(RGBLIGHT_MODE_STATIC_LIGHT);
      break;
  }

  return state;
}