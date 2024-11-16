/* Copyright 2023 Brian Low
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
#include "raw_hid.h"

// lt = layer toggle
#define LT_F LT(_ARROWS, KC_F)
#define LT_J LT(_ARROWS, KC_J)

#define LT_D LT(_NUMPAD, KC_D)
#define LT_K LT(_NUMPAD, KC_K)


#define O_LEFT LALT(KC_LEFT)
#define O_RGHT LALT(KC_RIGHT)
#define OS_LEFT LSFT(LALT(KC_LEFT))
#define OS_RGHT LSFT(LALT(KC_RIGHT))

enum sofle_layers {
    _QWERTY,
    _ARROWS,
    _NUMPAD,
};

enum custom_keycodes {
    JL_MEH = SAFE_RANGE,
    SW_LEFT,
    SW_RGHT,
    JL_LCBR,
    JL_RCBR,
    JL_LBRC,
    JL_RBRC,
    JLM_ARRW,
    JLM_IF,
    JLM_CLOG,
    JLM_TRYC,
    JLM_FUNC,
    JLM_CLBK,
    JLM_CLTG,
    JLM_NAME,
    JLM_PHON,
    JLM_EMAL,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case JL_MEH:
            if (record->event.pressed) {
                register_code(KC_LALT);
                register_code(KC_LCTL);
                register_code(KC_LGUI);
            } else {
                unregister_code(KC_LALT);
                unregister_code(KC_LCTL);
                unregister_code(KC_LGUI);
            }
            return false;

        // Select word: end with cursor on the left or the right
        case SW_LEFT:
            if(record->event.pressed) {
                tap_code16(LALT(KC_RGHT));
                tap_code16(LSFT(LALT(KC_LEFT)));
            }
            return false;
        case SW_RGHT:
            if(record->event.pressed) {
                tap_code16(LALT(KC_LEFT));
                tap_code16(LSFT(LALT(KC_RGHT)));
            }
            return false;

        // Brace and bracket. Holding down space disables the key. This should train
        // me to use the correct modifier instead of pressing strange combinations
        // to get the character I want.
        case JL_LCBR:
            if(record->event.pressed) {
                if (!(get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))) { SEND_STRING("{"); }
            }
            return false;
        case JL_RCBR:
            if(record->event.pressed) {
                if (!(get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))) { SEND_STRING("}"); }
            }
            return false;
        case JL_LBRC:
            if(record->event.pressed) {
                if (!(get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))) { SEND_STRING("["); }
            }
            return false;
        case JL_RBRC:
            if(record->event.pressed) {
                if (!(get_mods() & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))) { SEND_STRING("]"); }
            }
            return false;

        // Macros
        case JLM_ARRW:
            if(record->event.pressed) {
                SEND_STRING("() => {}");
                SEND_STRING(SS_TAP(X_LEFT));
            }
            return false;
        case JLM_IF:
            if(record->event.pressed) {
                SEND_STRING("if() {}");
                for(int i=0; i<4; i++) {
                    SEND_STRING(SS_TAP(X_LEFT));
                }
            }
            return false;
        case JLM_CLOG:
            if(record->event.pressed) {
                SEND_STRING("console.log('JIL', );");
                SEND_STRING(SS_TAP(X_LEFT));
                SEND_STRING(SS_TAP(X_LEFT));
            }
            return false;
        case JLM_TRYC:
            if(record->event.pressed) {
                SEND_STRING("try {} catch(error) {}");
                for(int i=0; i<17; i++) {
                    SEND_STRING(SS_TAP(X_LEFT));
                }
            }
            return false;
        case JLM_FUNC:
            if(record->event.pressed) {
                SEND_STRING("const  = () => {}");
                for(int i=0; i<11; i++) {
                    SEND_STRING(SS_TAP(X_LEFT));
                }
            }
            return false;
        case JLM_CLTG:
            if(record->event.pressed) { SEND_STRING("</"); }
            return false;
        case JLM_CLBK:
            if(record->event.pressed) { SEND_STRING("/>"); }
            return false;
        case JLM_NAME:
            if(record->event.pressed) { SEND_STRING("---"); }
            return false;
        case JLM_PHON:
            if(record->event.pressed) { SEND_STRING("---"); }
            return false;
        case JLM_EMAL:
            if(record->event.pressed) { SEND_STRING("---"); }
            return false;
    }
    return true;  // Process all other keycodes normally
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
[_QWERTY] = LAYOUT(
    KC_GRV,   KC_EXLM, KC_AT,   KC_HASH, KC_DLR,  KC_PERC,                                     KC_CIRC, KC_AMPR, KC_ASTR, _______, _______, KC_EQL,
    KC_TAB,   KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                                        KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
    JL_MEH,   KC_A,    KC_S,    LT_D,    LT_F,    KC_G,                                        KC_H,    LT_J,    LT_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,  KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    _______,                 _______,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
                       KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,  KC_ENT,          KC_ESC, KC_BSPC,   KC_RGUI, KC_RALT, KC_RCTL
),

[_ARROWS] = LAYOUT(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,                           KC_F6,    KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, _______, _______, JL_LBRC, JL_RBRC,  _______,                         _______,  O_LEFT,  KC_UP,   O_RGHT,  _______, KC_F12,
    _______, _______, _______, JL_LCBR, JL_RCBR,  _______,                         _______,  KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
    _______, _______, _______, KC_LPRN, KC_RPRN,  _______, _______,       _______, JLM_CLTG, KC_LABK, KC_RABK, JLM_CLBK, _______, _______,
                      _______, _______, _______,  _______, _______,       KC_DEL,  _______,  _______, _______, _______
),

[_NUMPAD] = LAYOUT(
    QK_BOOT, _______, _______, _______,  _______,  _______,                        _______,   _______, _______, _______, _______, _______,
    _______, _______, _______, JLM_TRYC, JLM_IF,   JLM_NAME,                       _______,   KC_KP_7, KC_KP_8, KC_KP_9, _______, _______,
    _______, _______, _______, JLM_FUNC, JLM_ARRW, JLM_PHON,                       KC_KP_DOT, KC_KP_4, KC_KP_5, KC_KP_6, _______, _______,
    _______, _______, _______, _______,  JLM_CLOG, JLM_EMAL, _______,     _______, KC_KP_0,   KC_KP_1, KC_KP_2, KC_KP_3, _______, _______,
                      _______, _______,  _______,  _______,  _______,     _______, _______,   KC_KP_0, KC_KP_DOT, _______
),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        clockwise ? rgb_matrix_increase_hue() : rgb_matrix_decrease_hue();
    } else {
        clockwise ? rgb_matrix_step() : rgb_matrix_step_reverse();
    }
    return false;
}

void keyboard_post_init_user(void) {
    rgblight_enable();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_TYPING_HEATMAP);
    rgb_matrix_sethsv_noeeprom(HSV_BLUE);
}

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    return is_keyboard_master() ? OLED_ROTATION_270 : rotation;
}

bool caps_word_active = false;

bool oled_task_user() {
    oled_clear();
    if (is_keyboard_master()) {
        oled_set_cursor(0, 0);
        switch (get_highest_layer(layer_state)) {
            case _ARROWS:
                oled_write("arrow", false);
                break;
            case _NUMPAD:
                oled_write("num", false);
                break;
            default:
                oled_write("alpha", false);
                break;
        }

        uint8_t rgb_mode = rgblight_get_mode();

        oled_set_cursor(0, 1);
        oled_write("l ", false);
        oled_write(get_u8_str(rgb_mode, ' '), false);

        oled_set_cursor(0, 2);
        oled_write("h ", false);
        oled_write(get_u8_str(rgb_matrix_get_hsv().h, ' '), false);

        oled_set_cursor(0, 3);
        oled_write("wc", false);
        oled_write(get_u8_str(get_current_wpm(), ' '), false);

        oled_set_cursor(0, 4);
        oled_write(caps_word_active ? "caps" : "    ", false);
    }

    return false;
}

void caps_word_set_user(bool active) {
    caps_word_active = active;
}
