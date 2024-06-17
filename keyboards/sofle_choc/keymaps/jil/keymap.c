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

// Left-hand home row mods
#define CTL_A LCTL_T(KC_A)
#define ALT_S LALT_T(KC_S)
#define SFT_F LSFT_T(KC_F)
#define GUI_D LGUI_T(KC_D)

// Right-hand home row mods
#define GUI_K RGUI_T(KC_K)
#define SFT_J RSFT_T(KC_J)
#define ALT_L LALT_T(KC_L)
#define CTL_SCLN RCTL_T(KC_SCLN)

#define Q_MOD LT(_Q, KC_Q)
#define TAB_MEH MEH_T(KC_TAB)
#define DEL_WORD LALT(KC_BSPC)
#define DEL_LINE LGUI(KC_BSPC)
#define ARR_ESC LT(_ARROWS, KC_ESC)
#define SYM_V LT(_V, KC_V)
#define SYM_M LT(_M, KC_M)

enum sofle_layers {
    _QWERTY,
    _ARROWS,
    _Q,
    _V,
    _M,
};

enum custom_keycodes {
    KC_OPT_CTRL_CMD = SAFE_RANGE,
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_OPT_CTRL_CMD:
            if (record->event.pressed) {
                register_code(KC_LALT);     // Option key
                register_code(KC_LCTL);     // Control key
                register_code(KC_LGUI);     // Command key
            } else {
                unregister_code(KC_LALT);
                unregister_code(KC_LCTL);
                unregister_code(KC_LGUI);
            }
            return false;  // Skip all further processing of this key
    }
    return true;  // Process all other keycodes normally
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * QWERTY
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | ESC  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Tab  |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
     * |------+------+------+------+------+------|  Mute |    | Pause |------+------+------+------+------+------|
     * |LShift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |RShift|
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | LCTL | LGUI | LCMD | LALT | /Enter  /       \Space \  | RALT | RCMD | RGUI | RCTL |
     *            |      |      |      |      |/       /         \      \ |      |      |      |      |
     *            `----------------------------------'           '------''---------------------------'
     */

[_QWERTY] = LAYOUT(
    KC_GRV,   KC_1,   KC_2,    KC_3,    KC_4,    KC_5,                                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL,
    KC_TAB,   KC_Q,  KC_W,    KC_E,    KC_R,    KC_T,                                          KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS,
    KC_OPT_CTRL_CMD,   KC_A,  KC_S,    KC_D,    LT(_ARROWS, KC_F),    KC_G,                             KC_H,    LT(_ARROWS, KC_J),    KC_K,    KC_L,    KC_SCLN, KC_QUOT,
    KC_LSFT,  KC_Z,  KC_X,    KC_C,    KC_V,    KC_B,    KC_MUTE,                   KC_MPLY,   KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, KC_BSLS,
                     KC_LCTL, KC_LALT, KC_LGUI, KC_SPC,  KC_ENT,            KC_ESC, KC_BSPC,   _______,   _______,  _______
),

[_ARROWS] = LAYOUT(
    _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,    KC_F5,                           KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
    _______, _______, _______, KC_LCBR, KC_RBRC,  KC_VOLU,                         KC_MNXT, _______, KC_UP,   _______, _______, KC_F12,
    _______, KC_LSFT, _______, KC_LBRC, KC_RBRC,  KC_VOLD,                         KC_MPRV, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
    _______, RGB_TOG, _______,  _______, _______, KC_MUTE, _______,       _______, KC_MPLY, _______, _______, _______, _______, _______,
                      _______, _______, _______,  _______, _______,       _______, KC_DEL,  _______, _______, _______
),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code16(LSA(KC_F2));
        } else {
            tap_code16(LSA(KC_F1));
        }
    } else {
        if (clockwise) {
            tap_code16(KC_MS_WH_UP);
        } else {
            tap_code16(KC_MS_WH_DOWN);
        }
    }
    return false;
}

#ifdef OLED_ENABLE
// Rotate OLED
// oled_rotation_t oled_init_user(oled_rotation_t rotation) {
//     return OLED_ROTATION_27 0;
// }
// Draw to OLED
bool oled_task_user() {
    // Set cursor position
    oled_set_cursor(0, 1);
    // Switch on current active layer
    switch (get_highest_layer(layer_state)) {
        case _ARROWS :
            oled_write("Arrow Layer", false);
            break;
        default :
            oled_write("Default Layer", false);
            break;
    }
    return false;
}
#endif
