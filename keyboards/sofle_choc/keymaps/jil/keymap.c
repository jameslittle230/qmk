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
    _______, _______, _______, KC_LCBR, KC_RCBR,  KC_VOLU,                         KC_MNXT, _______, KC_UP,   _______, _______, KC_F12,
    _______, KC_LSFT, _______, KC_LBRC, KC_RBRC,  KC_VOLD,                         KC_MPRV, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______,
    _______, RGB_TOG, _______,  _______, _______, KC_MUTE, _______,       _______, KC_MPLY, _______, _______, _______, _______, _______,
                      _______, _______, _______,  _______, _______,       _______, KC_DEL,  _______, _______, _______
),
};

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            rgb_matrix_increase_hue_noeeprom();
        } else {
            rgb_matrix_decrease_hue_noeeprom();
        }
    } else {
        if (clockwise) {
            rgb_matrix_step_noeeprom();
        } else {
            rgb_matrix_step_reverse_noeeprom();

        }
    }
    return false;
}

const char* get_rgb_effect_name(uint8_t effect) {
    switch (effect) {
        case RGB_MATRIX_NONE: return "None";
        case RGB_MATRIX_SOLID_COLOR: return "Solid Color";
        case RGB_MATRIX_ALPHAS_MODS: return "Alphas Mods";
        case RGB_MATRIX_GRADIENT_UP_DOWN: return "Gradient Up Down";
        case RGB_MATRIX_GRADIENT_LEFT_RIGHT: return "Gradient Left Right";
        case RGB_MATRIX_BREATHING: return "Breathing";
        case RGB_MATRIX_BAND_SAT: return "Band Saturation";
        case RGB_MATRIX_BAND_VAL: return "Band Value";
        case RGB_MATRIX_BAND_PINWHEEL_SAT: return "Band Pinwheel Saturation";
        case RGB_MATRIX_BAND_PINWHEEL_VAL: return "Band Pinwheel Value";
        case RGB_MATRIX_BAND_SPIRAL_SAT: return "Band Spiral Saturation";
        case RGB_MATRIX_BAND_SPIRAL_VAL: return "Band Spiral Value";
        case RGB_MATRIX_CYCLE_ALL: return "Cycle All";
        case RGB_MATRIX_CYCLE_LEFT_RIGHT: return "Cycle Left Right";
        case RGB_MATRIX_CYCLE_UP_DOWN: return "Cycle Up Down";
        case RGB_MATRIX_CYCLE_OUT_IN: return "Cycle Out In";
        case RGB_MATRIX_CYCLE_OUT_IN_DUAL: return "Cycle Out In Dual";
        case RGB_MATRIX_RAINBOW_MOVING_CHEVRON: return "Rainbow Moving Chevron";
        case RGB_MATRIX_CYCLE_PINWHEEL: return "Cycle Pinwheel";
        case RGB_MATRIX_CYCLE_SPIRAL: return "Cycle Spiral";
        case RGB_MATRIX_DUAL_BEACON: return "Dual Beacon";
        case RGB_MATRIX_RAINBOW_BEACON: return "Rainbow Beacon";
        case RGB_MATRIX_RAINBOW_PINWHEELS: return "Rainbow Pinwheels";
        // case RGB_MATRIX_FLOWER_BLOOMING: return "Flower Blooming";
        case RGB_MATRIX_RAINDROPS: return "Raindrops";
        case RGB_MATRIX_JELLYBEAN_RAINDROPS: return "Jellybean Raindrops";
        case RGB_MATRIX_HUE_BREATHING: return "Hue Breathing";
        case RGB_MATRIX_HUE_PENDULUM: return "Hue Pendulum";
        case RGB_MATRIX_HUE_WAVE: return "Hue Wave";
        case RGB_MATRIX_PIXEL_FRACTAL: return "Pixel Fractal";
        case RGB_MATRIX_PIXEL_FLOW: return "Pixel Flow";
        case RGB_MATRIX_PIXEL_RAIN: return "Pixel Rain";
        // case RGB_MATRIX_TYPING_HEATMAP: return "Typing Heatmap";
        // case RGB_MATRIX_DIGITAL_RAIN: return "Digital Rain";
        // case RGB_MATRIX_SOLID_REACTIVE_SIMPLE: return "Solid Reactive Simple";
        // case RGB_MATRIX_SOLID_REACTIVE: return "Solid Reactive";
        // case RGB_MATRIX_SOLID_REACTIVE_WIDE: return "Solid Reactive Wide";
        // case RGB_MATRIX_SOLID_REACTIVE_MULTIWIDE: return "Solid Reactive Multiwide";
        // case RGB_MATRIX_SOLID_REACTIVE_CROSS: return "Solid Reactive Cross";
        // case RGB_MATRIX_SOLID_REACTIVE_MULTICROSS: return "Solid Reactive Multicross";
        // case RGB_MATRIX_SOLID_REACTIVE_NEXUS: return "Solid Reactive Nexus";
        // case RGB_MATRIX_SOLID_REACTIVE_MULTINEXUS: return "Solid Reactive Multinexus";
        // case RGB_MATRIX_SPLASH: return "Splash";
        // case RGB_MATRIX_MULTISPLASH: return "Multisplash";
        // case RGB_MATRIX_SOLID_SPLASH: return "Solid Splash";
        // case RGB_MATRIX_SOLID_MULTISPLASH: return "Solid Multisplash";
        // case RGB_MATRIX_STARLIGHT: return "Starlight";
        // case RGB_MATRIX_STARLIGHT_DUAL_HUE: return "Starlight Dual Hue";
        // case RGB_MATRIX_STARLIGHT_DUAL_SAT: return "Starlight Dual Saturation";
        // case RGB_MATRIX_RIVERFLOW: return "Riverflow";
        default: return "Unknown";
    }
}

// Override the layer state set function
layer_state_t layer_state_set_user(layer_state_t state) {
    // TODO: temporarily switch into solid color LED mode when switching to
    // a non-default layer
    return state;
}

void keyboard_post_init_user(void) {
    // Enable RGB lighting if it's not already enabled
    rgblight_enable();
    // Set the initial RGB color for the default layer
    rgblight_sethsv_noeeprom(HSV_RED);
}

bool oled_task_user() {
    oled_clear();
    oled_set_cursor(0, 0);
    switch (get_highest_layer(layer_state)) {
        case _ARROWS :
            oled_write("Arrow Layer", false);
            break;
        default :
            oled_write("Default Layer", false);
            break;
    }

    uint8_t rgb_mode = rgblight_get_mode();
    const char* rgb_effect_name = get_rgb_effect_name(rgb_mode);

    oled_set_cursor(0, 1);
    oled_write(rgb_effect_name, false);
    return false;
}
