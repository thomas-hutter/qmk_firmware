 /* Copyright 2024 @ Keychron (https://www.keychron.com)
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

#ifdef RGB_MATRIX_ENABLE
/* RGB Matrix driver configuration */
#    define DRIVER_COUNT 2
#    define DRIVER_1_LED_COUNT 44
#    define DRIVER_2_LED_COUNT 25
#    define RGB_MATRIX_LED_COUNT (DRIVER_1_LED_COUNT + DRIVER_2_LED_COUNT)

#    define SPI_SCK_PIN A5
#    define SPI_MISO_PIN A6
#    define SPI_MOSI_PIN A7

#    define DRIVER_CS_PINS \
        { B8, B9 }
#    define SNLED23751_SPI_DIVISOR 16
#    define SPI_DRIVER SPID1 

/* Scan phase of led driver set as MSKPHASE_9CHANNEL(defined as 0x03 in snled27351.h) */
#    define SNLED27351_PHASE_CHANNEL MSKPHASE_9CHANNEL

/* Set LED driver current */
#    define SNLED27351_CURRENT_TUNE \
         { 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c, 0x2c}
        
/* Set to infinit, which is use in USB mode by default */
#    define RGB_MATRIX_TIMEOUT RGB_MATRIX_TIMEOUT_INFINITE

/* Allow shutdown of led driver to save power */
#    define RGB_MATRIX_DRIVER_SHUTDOWN_ENABLE

/* Turn off backlight on low brightness to save power */
#    define RGB_MATRIX_BRIGHTNESS_TURN_OFF_VAL 32

/* Indicator */
#    define BT_HOST_LED_MATRIX_LIST \
        {  16, 17, 18 }

#    define P2P4G_HOST_LED_MATRIX_LIST \
        { 19 }

#    define BAT_LEVEL_LED_LIST \
        { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 }

#    define CAPS_LOCK_INDEX 30
#    define LOW_BAT_IND_INDEX \
        { 61, 64 }

#    define RGB_MATRIX_KEYPRESSES
#    define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#endif

// Tap-hold configuration for home row mods.
#define TAPPING_TERM 200
#define TAPPING_TERM_EXTRA 100
#define TAPPING_TERM_PER_KEY
#define TAP_CODE_DELAY 5

#define PERMISSIVE_HOLD
// #define QUICK_TAP_TERM_PER_KEY

#define ACHORDION_STREAK
#define ACHORDION_TIMEOUT 500

// #define CAPS_WORD_INVERT_ON_SHIFT // Holding Shift while Caps Word is active inverts the shift state.
#define CAPS_WORD_IDLE_TIMEOUT 5000 // When idle, turn off Caps Word after 5 seconds.
#define DOUBLE_TAP_SHIFT_TURNS_ON_CAPS_WORD
// #define CAPS_WORD_STRONG_SNAKE_CASE

// #define COMBO_SHOULD_TRIGGER
#define COMBO_ONLY_FROM_LAYER 1
#define COMBO_TERM_PER_COMBO
#define COMBO_TERM 40
#define COMBO_TERM_SLOW 100
#define COMBO_TERM_DIRECTIONAL  1000
#define COMBO_TERM_DIRECTIONAL_2HANDS 2000
#define COMBO_STRICT_TIMER
// #define COMBO_MUST_PRESS_IN_ORDER
// #define COMBO_MUST_PRESS_IN_ORDER_PER_COMBO
#define REQUIRE_PRIOR_IDLE_TIMEOUT 30

// When idle, turn off Layer Lock after 60 seconds.
#define LAYER_LOCK_IDLE_TIMEOUT 60000
// When idle, turn off NAV layer after 60 seconds.
#define NAV_LAYER_TIMEOUT 30000
// When idle, set MAGIC key to default action 
#define MAGIC_LAYER_TIMEOUT 600

#define LEADER_PER_KEY_TIMING
#define LEADER_NO_TIMEOUT
#define LEADER_TIMEOUT 300

#define MY_EMAIL "th.hutter@gmail.com"
#define MY_PRIVATE_EMAIL "th.hutter@proton.me"
#define MY_WORK_USERNAME "hrt5wi"
#define MY_WORK_EMAIL "thomas.hutter@bosch.com"

#define SELECT_WORD_TIMEOUT 1000

// #define AUTO_SHIFT_NO_AUTO_REPEAT_PER_KEY
// #define AUTO_SHIFT_TIMEOUT 250
// #define NO_AUTO_SHIFT_NUMERIC
// #define NO_AUTO_SHIFT_ALPHA
// #define AUTO_SHIFT_SPECIAL

