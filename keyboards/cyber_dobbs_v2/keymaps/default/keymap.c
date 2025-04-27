// Copyright 2023 QMK
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "quantum.h"
#include "qp.h"
#include "qp_st7789.h"        // Add this line for your specific display
#include "color.h"            // Add this for COLOR constants
#include "fonts/myfont.qff.h"


void keyboard_post_init_user(void) {
    // Initialize the display first
    painter_device_t my_display = qp_st7789_make_spi_device(
        DISPLAY_WIDTH, DISPLAY_HEIGHT,
        DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, 
        DISPLAY_ROTATION, DISPLAY_BACKLIGHT_PIN);
    
    // Start the quantum painter engine
    qp_init(my_display, DISPLAY_ROTATION);
    
    if (my_display) {
        // Clear the display
        qp_rect(my_display, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, 0, 0, true);

    }
}

bool oled_task_user(void) {
    static painter_device_t display = NULL;
    
    // Get the display handle if we don't have it yet
    if (!display) {
        display = qp_st7789_make_spi_device(
            DISPLAY_WIDTH, DISPLAY_HEIGHT,
            DISPLAY_CS_PIN, DISPLAY_DC_PIN, DISPLAY_RST_PIN, 
            DISPLAY_ROTATION, DISPLAY_BACKLIGHT_PIN);
    }
    
    if (display) {
        // Clear the display
        qp_rect(display, 0, 0, DISPLAY_WIDTH, DISPLAY_HEIGHT, 0, 0, 0, true);

        // Draw text
        painter_font_handle_t font = qp_load_font_mem(font_myfont);

        // Then use the correct parameter order
        qp_drawtext(display, 0, 0, font, "Hello, world!");
    }

    return false;  // important! (don't refresh OLED separately)
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) { /* First encoder */
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    }
    return false;
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    [0] = LAYOUT(
        KC_MINUS,   KC_SLSH,   KC_KP_ASTERISK, KC_BACKSPACE,
        KC_7,   KC_8,   KC_9, KC_KP_PLUS,
        KC_4,   KC_5,   KC_6, KC_1,
        KC_2,   KC_3,   KC_0, KC_DOT,
        KC_ENTER
    )
};
