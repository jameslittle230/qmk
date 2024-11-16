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
#pragma once

// Enabling this option changes the startup behavior to listen for an
// active USB communication to delegate which part is master and which
// is slave. With this option enabled and theres’s USB communication,
// then that half assumes it is the master, otherwise it assumes it
// is the slave.
//
// I've found this helps with some ProMicros where the slave does not boot
#define SPLIT_USB_DETECT

#define RGB_MATRIX_SLEEP     // turn off effects when suspended
#define SPLIT_TRANSPORT_MIRROR             // If LED_MATRIX_KEYPRESSES or LED_MATRIX_KEYRELEASES is enabled, you also will want to enable SPLIT_TRANSPORT_MIRROR
#define RGB_MATRIX_MAXIMUM_BRIGHTNESS 100  // limits maximum brightness of LEDs (max 255). Higher may cause the controller to crash.
#define SPLIT_LAYER_STATE_ENABLE
#define SPLIT_LED_STATE_ENABLE

#undef LOCKING_SUPPORT_ENABLE
#undef LOCKING_RESYNC_ENABLE
#define NO_MUSIC_MODE
#define LAYER_STATE_8BIT

#define RGB_TRIGGER_ON_KEYDOWN

#define WPM_LAUNCH_CONTROL
#define WPM_ALLOW_COUNT_REGRESSION

#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
#define CAPS_WORD_IDLE_TIMEOUT 0

#define ENABLE_RGB_MATRIX_TYPING_HEATMAP
// #define ENABLE_RGB_MATRIX_MULTISPLASH
// #define ENABLE_RGB_MATRIX_DIGITAL_RAIN
// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
// #define ENABLE_RGB_MATRIX_SOLID_REACTIVE

#define RGB_MATRIX_TYPING_HEATMAP_DECREASE_DELAY_MS 25
#define RGB_MATRIX_TYPING_HEATMAP_SPREAD 40
#define RGB_MATRIX_TYPING_HEATMAP_COLOR_COUNT 3
