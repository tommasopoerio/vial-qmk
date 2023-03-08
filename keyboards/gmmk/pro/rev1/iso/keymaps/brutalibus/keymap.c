/* Copyright 2021 Glorious, LLC <salman@pcgamingrace.com>
   Copyright 2021 Jonavin Eng @Jonavin
   Copyright 2022 RustyBrakes (ISO conversion)
   Copyright 2022 gourdo1 <gourdo1@outlook.com>
   
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

// Note: Many advanced functions referenced in this file are defined in /users/brutalibus/brutalibus.c

#include QMK_KEYBOARD_H

#include "rgb_matrix_map.h"

#include "brutalibus.h"

#include <math.h>

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

    /* Base Layout
     *
     * ,-------------------------------------------------------------------------------------------------------------.
     * | Esc  ||  F1  |  F2  |  F3  |  F4  ||  F5  |  F6  |  F7  |  F8  ||  F9  | F10  | F11  | F12  || Home || Mute |
     * |=============================================================================================================|
     * | ISO  |  1 ! |  2 @ |  3 # |  4 $ |  5 % |  6 ^ |  7 & |  8 * |  9 ( |  0 ) |  - _ |  = + |  Backspc || Del  |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+----------++------|
     * |   Tab   |  Q   |  W   |  E   |  R   |  T   |  Y   |  U   |  I   |  O   |  P   | [ }  | ] }  |       || PgUp |
     * |---------+------+------+------+------+------+------+------+------+------+------+------+------+       ++------|
     * |  Capslock  |  A   |  S   |  D   |  F  |  G   |  H   |  J   |  K   |  L   | ; :  | ' "  | ISO| Enter || PgDn |
     * |------------+------+------+------+-----+------+------+------+------+------+------+------|----+========+------|
     * | LShift | ISO |  Z   |  X   |  C   |  V   |  B   |  N   |  M   | , <  | . >  | / ?  | RShift ||  Up  || End  |
     * |--------------+------+------+------+------+------+------+------+------+------+------+--+=====++------++======|
     * |  Ctrl  |   Win  |  LAlt  |               Space                  | RAlt |  Fn  | Ctrl || Left | Down | Rght |
     * `------------------------------------------------------------------------------------------------------------'
     */

    [_BASE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  LEFTOFENC,        ENCFUNC,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          BELOWENC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,                   KC_PGUP,
        CAPSNUM, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,           KC_PGDN,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, KC_LGUI, KC_LALT,                            KC_SPC,                             KC_RALT, MO(_FN1),KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    /* GAMEMODE Layout
     *
     * ,-------------------------------------------------------------------------------------------------------------.
     * | Esc  ||  F1  |  F2  |  F3  |  F4  ||  F5  |  F6  |  F7  |  F8  ||  F9  | F10  | F11  | F12  || Home || Mute |
     * |=============================================================================================================|
     * | ISO  |  1 ! |  2 @ |  3 # |  4 $ |  5 % |  6 ^ |  7 & |  8 * |  9 ( |  0 ) |  - _ |  = + |  Backspc || Del  |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+----------++------|
     * |   Tab   |  Q   |  W   |  E   |  R   |  T   |  Y   |  U   |  I   |  O   |  P   | [ }  | ] }  |       || PgUp |
     * |---------+------+------+------+------+------+------+------+------+------+------+------+------+       ++------|
     * |  Capslock  |  A   |  S   |  D   |  F  |  G   |  H   |  J   |  K   |  L   | ; :  | ' "  | ISO| Enter || PgDn |
     * |------------+------+------+------+-----+------+------+------+------+------+------+------|----+========+------|
     * | LShift | ISO |  Z   |  X   |  C   |  V   |  B   |  N   |  M   | , <  | . >  | / ?  | RShift ||  Up  || End  |
     * |--------------+------+------+------+------+------+------+------+------+------+------+--+=====++------++======|
     * |  Ctrl  |   TD(0)  |  LAlt  |               Space                 | RAlt |  Fn  | Ctrl || Left | Down | Rght |
     * `------------------------------------------------------------------------------------------------------------'
     */


     [_GAMEMODE] = LAYOUT(
        KC_ESC,  KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  LEFTOFENC,        ENCFUNC,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  KC_BSPC,          BELOWENC,
        KC_TAB,  KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_LBRC, KC_RBRC,                   KC_PGUP,
        KC_CAPSLOCK, KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, KC_NUHS, KC_ENT,           KC_PGDN,
        KC_LSFT, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        KC_LCTL, TD(0), KC_LALT,                            KC_SPC,                             KC_RALT, _______,KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),

    


    /* _NUMPADMOUSE Layout
     *  Note: A symbol preceded by "P" is a Numpad-encoded version of the key -- any app that differentiates will recognize the char as coming from a physical numpad.
     * ,-------------------------------------------------------------------------------------------------------------.
     * | ____ || ____ | ____ | ____ | ____ || ____ | ____ | ____ | ____ || ____ | ____ | ____ | ____ || ____ || ____ |
     * |=============================================================================================================|
     * | ____ |  P1  |  P2  |  P3  |  P4  |  P5  |  P6  |  P7  |  P8  |  P9  |  P0  |  P-  |  P+  | ________ || ____ |
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+----------++------|
     * |  ______ | PGUP |  Up  | PGDN | None | None | None |  P4  |  P5  |  P6  |  P+  | ____ | ____ |       || WhUp |
     * |---------+------+------+------+------+------+------+------+------+------+------+------+------+       ++------|
     * |  ________  | Left | Down | Rght | None| None | None |  P1  |  P2  |  P3  |  P*  | ___ | ___ |P-Enter|| WhDn |
     * |------------+------+------+------+-----+------+------+------+------+------+------+------|----+========+------|
     * |  __________  | None | ____ | ____ | ____ | None | None |   0  |  00  |  P.  |  P/  |  MBt1  ||MS_UP || MBt2 |
     * |--------------+------+------+------+------+------+------+------+------+------+------+--+=====++------++======|
     * |  ____  |  ____  |  ____  |               _____                  | ____ | ____ | MBt3 ||MS_LT |MS_DN |MS_RT |
     * `------------------------------------------------------------------------------------------------------------'
     */

    [_NUMPADMOUSE] = LAYOUT(
        _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______, _______,          _______,
        _______, KC_P1,   KC_P2,   KC_P3,   KC_P4,   KC_P5,   KC_P6,   KC_P7,   KC_P8,   KC_P9,   KC_P0,   KC_PMNS, KC_PPLS, _______,          _______,
        _______, KC_PGUP, KC_UP,   KC_PGDN, KC_NO,   KC_NO,   KC_NO,   KC_P4,   KC_P5,   KC_P6,   KC_PPLS, _______, _______,                   KC_WH_U,
        _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_NO,   KC_NO,   KC_NO,   KC_P1,   KC_P2,   KC_P3,   KC_PAST, _______, _______, KC_PENT,          KC_WH_D,
        _______, _______, KC_NO,   _______, _______, _______, _______, _______, KC_P0,   KC_00,   KC_PDOT, KC_PSLS,          KC_BTN1, KC_MS_U, KC_BTN2,
        _______, _______, _______,                            KC_PENT,                            _______, _______, KC_BTN3, KC_MS_L, KC_MS_D, KC_MS_R
    ),

/* FN1 Layout
     *
     * ,-------------------------------------------------------------------------------------------------------------.
     * | Esc  ||MyCmp |WbHom | Calc |MdSel ||MdPrv |MdNxt |MdPly |MdStp ||VolDn |VolUp |PrScr |ScrLk ||Pause ||Sleep |
     * |=============================================================================================================|
     * | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ | ____ |RGBTOD|RGBTOI| ________ ||RGBTOG|
     * |------+------+------+------+------+------+------+------+------+------+------+------+------+----------++------|
     * |  ______ |RGBSAD|RGBVAI|RGBSAI| NKRO | ____ |YAHOO | ____ | ____ |OUTLK |Pause | ____ | ____ |       || Home |
     * |---------+------+------+------+------+------+------+------+------+------+------+------+------+       ++------|
     * |  Capslock  |RGBHUD|RGBVAD|RGBHUI| ____|GMAIL |HTMAIL| ____ | ____ | ____ | ____ | ____ | ___ | ____ || End  |
     * |------------+------+------+------+-----+------+------+------+------+------+------+------|----+========+------|
     * |  ____ |QK_BOOT|RGBNIT| ____ | ____ | ____ | ____ |NumLk | ____ | ____ |DOTCOM| CAD  | ______ ||RGBMOD|| ____ |
     * |--------------+------+------+------+------+------+------+------+------+------+------+--+=====++------++======|
     * |  ____  | GameMode |  ____  |              _____                  | ____ | ____ | ____ ||RGBSPD|RGBRMD|RGBSPI|
     * `------------------------------------------------------------------------------------------------------------'
     */


    [_FN1] = LAYOUT(
        EE_CLR,  KC_MYCM, KC_WHOM, KC_CALC, KC_MSEL, KC_MPRV, KC_MNXT, KC_MPLY, KC_MSTP, KC_VOLD, KC_VOLU, KC_PSCR, KC_SLCK, KC_PAUS,           KC_SLEP,
        PRNCONF, TG_CAPS, TG_PAD,  TG_ESC,  TG_DEL,  TG_TDCAP,TG_ENC,  TG_INS,TG_SPCMOD,_______,TG_ENGCAP,RGB_TOD,RGB_TOI, _______,           RGB_TOG,
        _______, RGB_SAD, RGB_VAI, RGB_SAI, NK_TOGG, _______, YAHOO,   _______, _______, OUTLOOK, KC_PAUS, SWAP_L,  SWAP_R,                     KC_HOME,
        KC_CAPS, RGB_HUD, RGB_VAD, RGB_HUI, _______, GMAIL,   HOTMAIL, _______, _______, LOCKPC,  _______, _______, _______, _______,           KC_END,
        _______, QK_BOOT, RGB_NITE,_______, _______, _______, QK_BOOT, KC_NLCK, _______, _______, DOTCOM,  KC_CAD,           _______, RGB_MOD,  _______,
        _______, TG(_GAMEMODE), _______,                            _______,                            _______, _______, _______, RGB_SPD, RGB_RMOD, RGB_SPI
    ),

    #ifdef COLEMAK_LAYER_ENABLE
    [_COLEMAK] = LAYOUT(
        _______, KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,  _______,          _______,
        KC_GRV,  KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_MINS, KC_EQL,  _______,          _______,
        KC_TAB,  KC_Q,    KC_W,    KC_F,    KC_P,    KC_G,    KC_J,    KC_L,    KC_U,    KC_Y,    KC_SCLN, KC_LBRC, KC_RBRC,                   KC_PGUP,
        _______, KC_A,    KC_R,    KC_S,    KC_T,    KC_D,    KC_H,    KC_N,    KC_E,    KC_I,    KC_O,    KC_QUOT, KC_NUHS, KC_ENT,           KC_PGDN,
        _______, KC_NUBS, KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_K,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH,          KC_RSFT, KC_UP,   KC_END,
        _______, _______, _______,                            KC_SPC,                             KC_RALT, _______, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
    ),
    #endif // COLEMAK_LAYER_ENABLE
};

#if defined(ENCODER_ENABLE) && !defined(ENCODER_DEFAULTACTIONS_ENABLE) // Encoder Functionality when not using userspace defaults
void encoder_action_rgbhue(bool clockwise) {
    if (clockwise)
        rgblight_increase_hue_noeeprom();
    else
        rgblight_decrease_hue_noeeprom();
}

bool encoder_update_user(uint8_t index, bool clockwise) {
    uint8_t mods_state = get_mods();
    if (mods_state & MOD_BIT(KC_LSFT)) { // If you are holding L shift, encoder changes layers
        encoder_action_layerchange(clockwise);
    } else if (mods_state & MOD_BIT(KC_RSFT)) { // If you are holding R shift, Page up/dn
        unregister_mods(MOD_BIT(KC_RSFT));
        encoder_action_navpage(clockwise);
        register_mods(MOD_BIT(KC_RSFT));
    } else if (mods_state & MOD_BIT(KC_LCTL)) { // if holding Left Ctrl, navigate next/prev word
        encoder_action_navword(clockwise);
    } else if (mods_state & MOD_BIT(KC_RCTL)) { // if holding Right Ctrl, change rgb hue/colour
        encoder_action_rgbhue(clockwise);
    } else if (mods_state & MOD_BIT(KC_LALT)) { // if holding Left Alt, change media next/prev track
        encoder_action_mediatrack(clockwise);
    } else {
        switch (get_highest_layer(layer_state)) {
        case _FN1:
            #ifdef IDLE_TIMEOUT_ENABLE
            timeout_update_threshold(clockwise);
            #endif
            break;
        default:
            encoder_action_volume(clockwise); // Otherwise it just changes volume
            break;
        }
    }
    //return true; //set to return false to counteract enabled encoder in pro.c
    return false;
}
#endif // ENCODER_ENABLE && !ENCODER_DEFAULTACTIONS_ENABLE

#ifdef RGB_MATRIX_ENABLE


// Capslock, Scroll lock and Numlock indicator on Left side lights.
void rgb_matrix_indicators_advanced_user(uint8_t led_min, uint8_t led_max) {
    if (get_rgb_nightmode()) rgb_matrix_set_color_all(RGB_OFF);

    // Scroll Lock RGB setup
    if (IS_HOST_LED_ON(USB_LED_SCROLL_LOCK)) {
        rgb_matrix_set_color(LED_L3, RGB_RED);
        rgb_matrix_set_color(LED_L4, RGB_RED);
        rgb_matrix_set_color(LED_TAB, RGB_RED);
        rgb_matrix_set_color(LED_F12, RGB_RED);
    }

/*
    // System NumLock warning indicator RGB setup
    #ifdef INVERT_NUMLOCK_INDICATOR
    if (!IS_HOST_LED_ON(USB_LED_NUM_LOCK)) { // on if NUM lock is OFF to bring attention to overlay numpad not functional when enabled
        rgb_matrix_set_color(LED_GRV, RGB_ORANGE2);
        rgb_matrix_set_color(LED_L1, RGB_ORANGE2);
        rgb_matrix_set_color(LED_L2, RGB_ORANGE2);
        rgb_matrix_set_color(LED_N, RGB_ORANGE2);
        rgb_matrix_set_color(LED_FN, RGB_ORANGE2);
    }
    #else
    if (IS_HOST_LED_ON(USB_LED_NUM_LOCK)) { // Normal, on if NUM lock is ON
        rgb_matrix_set_color(LED_GRV, RGB_ORANGE2);
        rgb_matrix_set_color(LED_L1, RGB_ORANGE2);
        rgb_matrix_set_color(LED_L2, RGB_ORANGE2);
        rgb_matrix_set_color(LED_N, RGB_ORANGE2);
        rgb_matrix_set_color(LED_FN, RGB_ORANGE2);
    }
    #endif // INVERT_NUMLOCK_INDICATOR
*/

    // CapsLock RGB setup
    if (IS_HOST_LED_ON(USB_LED_CAPS_LOCK)) {
        if (user_config.rgb_hilite_caps) {
            if (user_config.rgb_english_caps) {
                for (uint8_t i = 0; i < ARRAYSIZE(LED_LIST_LETTERS); i++) {
                    rgb_matrix_set_color(LED_LIST_LETTERS[i], RGB_CHARTREUSE);
                }
            }
            else {
                for (uint8_t i = 0; i < ARRAYSIZE(LED_LIST_LETTERS_DE); i++) {
                    rgb_matrix_set_color(LED_LIST_LETTERS_DE[i], RGB_CHARTREUSE);
                }
            }
            rgb_matrix_set_color(LED_L7, RGB_CHARTREUSE);
            rgb_matrix_set_color(LED_L8, RGB_CHARTREUSE);
            rgb_matrix_set_color(LED_LSFT, RGB_CHARTREUSE);
        }
        else {
            rgb_matrix_set_color(LED_L7, RGB_CHARTREUSE);
            rgb_matrix_set_color(LED_L8, RGB_CHARTREUSE);
            rgb_matrix_set_color(LED_LSFT, RGB_CHARTREUSE);
        }
    }


    // Fn selector mode RGB setup
    switch (get_highest_layer(layer_state)) { // special handling per layer
    case _FN1: // on Fn layer select what the encoder does when pressed
        rgb_matrix_set_color(LED_FN, RGB_RED); //FN key

        //NEW RGB LIGHTING TO RING KEYBOARD ON FN LAYER ACTIVATION:
        for (uint8_t j = 0; j < ARRAYSIZE(LED_LIST_FUNCROW); j++) {
            rgb_matrix_set_color(LED_LIST_FUNCROW[j], RGB_RED);
        }
        rgb_matrix_set_color(LED_LCTL, RGB_RED);
        rgb_matrix_set_color(LED_LALT, RGB_RED);
        rgb_matrix_set_color(LED_SPC, RGB_RED);
        rgb_matrix_set_color(LED_LWIN, RGB_RED);
        //rgb_matrix_set_color(LED_RALT, RGB_RED);
        rgb_matrix_set_color(LED_FN, RGB_OFFBLUE);
        //rgb_matrix_set_color(LED_RCTL, RGB_RED);
        rgb_matrix_set_color(LED_BSLS, RGB_RED);
        rgb_matrix_set_color(LED_L1, RGB_RED);
        rgb_matrix_set_color(LED_L2, RGB_RED);
        rgb_matrix_set_color(LED_L3, RGB_RED);
        rgb_matrix_set_color(LED_L4, RGB_RED);
        rgb_matrix_set_color(LED_L5, RGB_RED);
        rgb_matrix_set_color(LED_L6, RGB_RED);
        rgb_matrix_set_color(LED_L7, RGB_RED);
        rgb_matrix_set_color(LED_L8, RGB_RED);
        rgb_matrix_set_color(LED_DOWN, RGB_RED);
        rgb_matrix_set_color(LED_LEFT, RGB_RED);
        rgb_matrix_set_color(LED_RIGHT, RGB_RED);
        rgb_matrix_set_color(LED_R1, RGB_RED);
        rgb_matrix_set_color(LED_R2, RGB_RED);
        rgb_matrix_set_color(LED_R3, RGB_RED);
        rgb_matrix_set_color(LED_R4, RGB_RED);
        rgb_matrix_set_color(LED_R5, RGB_RED);
        rgb_matrix_set_color(LED_R6, RGB_RED);
        rgb_matrix_set_color(LED_R7, RGB_RED);
        rgb_matrix_set_color(LED_R8, RGB_RED);
        rgb_matrix_set_color(LED_MINS, RGB_OFFBLUE);
        rgb_matrix_set_color(LED_EQL, RGB_OFFBLUE);


        // System NumLock warning indicator RGB setup
        #ifdef INVERT_NUMLOCK_INDICATOR 
        if (!IS_HOST_LED_ON(USB_LED_NUM_LOCK)) { // on if NUM lock is OFF to bring attention to overlay numpad not functional when enabled
            rgb_matrix_set_color(LED_N, RGB_ORANGE2);
        }
        #else
        if (IS_HOST_LED_ON(USB_LED_NUM_LOCK)) { // Normal, on if NUM lock is ON
            rgb_matrix_set_color(LED_N, RGB_ORANGE2);
        }
        #endif // INVERT_NUMLOCK_INDICATOR

        //Add RGB statuses for user.config toggles
        if (user_config.rgb_hilite_caps) {
        rgb_matrix_set_color(LED_1, RGB_GREEN);
        } else {
        rgb_matrix_set_color(LED_1, RGB_PURPLE);
        }
        if (user_config.rgb_hilite_numpad) {
        rgb_matrix_set_color(LED_2, RGB_GREEN);
        } else {
        rgb_matrix_set_color(LED_2, RGB_PURPLE);
        }
        if (user_config.esc_double_tap_to_baselyr) {
        rgb_matrix_set_color(LED_3, RGB_GREEN);
        } else {
        rgb_matrix_set_color(LED_3, RGB_PURPLE);
        }
        if (user_config.del_right_home_top) {
        rgb_matrix_set_color(LED_4, RGB_GREEN);
        } else {
        rgb_matrix_set_color(LED_4, RGB_PURPLE);
        }
        if (user_config.double_tap_shift_for_capslock) {
        rgb_matrix_set_color(LED_5, RGB_GREEN);
        } else {
        rgb_matrix_set_color(LED_5, RGB_PURPLE);
        }
        if (user_config.encoder_press_mute_or_media) {
        rgb_matrix_set_color(LED_6, RGB_GREEN);
        } else {
        rgb_matrix_set_color(LED_6, RGB_PURPLE);
        }
        if (user_config.ins_on_shft_bkspc_or_del) {
        rgb_matrix_set_color(LED_7, RGB_GREEN);
        } else {
        rgb_matrix_set_color(LED_7, RGB_PURPLE);
        }
        if (user_config.disable_space_mods) {
        rgb_matrix_set_color(LED_8, RGB_GREEN);
        } else {
        rgb_matrix_set_color(LED_8, RGB_PURPLE);
        }
        if (user_config.rgb_english_caps) {
        rgb_matrix_set_color(LED_0, RGB_GREEN);
        } else {
        rgb_matrix_set_color(LED_0, RGB_PURPLE);
        }

        // Add RGB Timeout Indicator -- shows 0 to 139 using F row and num row; larger numbers using 16bit code
        uint16_t timeout_threshold = get_timeout_threshold();
        if (timeout_threshold <= 10) rgb_matrix_set_color(LED_LIST_FUNCROW[timeout_threshold], RGB_BLUE);
        else if (timeout_threshold < 140) {
            rgb_matrix_set_color(LED_LIST_FUNCROW[(timeout_threshold / 10)], RGB_CYAN);
            rgb_matrix_set_color(LED_LIST_FUNCROW[(timeout_threshold % 10)], RGB_BLUE);
        } else { // >= 140 minutes, just show these 3 lights
            rgb_matrix_set_color(LED_LIST_FUNCROW[10], RGB_CYAN);
            rgb_matrix_set_color(LED_LIST_FUNCROW[11], RGB_CYAN);
            rgb_matrix_set_color(LED_LIST_FUNCROW[12], RGB_CYAN);
        }
        break;

        // Numpad & Mouse Keys overlay RGB
    case _NUMPADMOUSE:
        #ifdef INVERT_NUMLOCK_INDICATOR 
        if (!IS_HOST_LED_ON(USB_LED_NUM_LOCK)) { // on if NUM lock is OFF to bring attention to overlay numpad not functional when enabled
            rgb_matrix_set_color(LED_N, RGB_ORANGE2);
        }
        #else
        if (IS_HOST_LED_ON(USB_LED_NUM_LOCK)) { // Normal, on if NUM lock is ON
            rgb_matrix_set_color(LED_N, RGB_ORANGE2);
        }
        #endif // INVERT_NUMLOCK_INDICATOR
        if (user_config.rgb_hilite_numpad) {
            for (uint8_t i = 0; i < ARRAYSIZE(LED_LIST_NUMPAD); i++) {
                rgb_matrix_set_color(LED_LIST_NUMPAD[i], RGB_OFFBLUE);
            }
            rgb_matrix_set_color(LED_L5, RGB_OFFBLUE);
            rgb_matrix_set_color(LED_L6, RGB_OFFBLUE);
            rgb_matrix_set_color(LED_CAPS, RGB_OFFBLUE);
            rgb_matrix_set_color(LED_UP, RGB_CHARTREUSE);
            rgb_matrix_set_color(LED_DOWN, RGB_CHARTREUSE);
            rgb_matrix_set_color(LED_LEFT, RGB_CHARTREUSE);
            rgb_matrix_set_color(LED_RIGHT, RGB_CHARTREUSE);
            rgb_matrix_set_color(LED_RCTL, RGB_CHARTREUSE);
            rgb_matrix_set_color(LED_RSFT, RGB_CHARTREUSE);
            rgb_matrix_set_color(LED_END, RGB_CHARTREUSE);
            rgb_matrix_set_color(LED_PGUP, RGB_CHARTREUSE);
            rgb_matrix_set_color(LED_PGDN, RGB_CHARTREUSE);
        } else {
            rgb_matrix_set_color(LED_L5, RGB_OFFBLUE);
            rgb_matrix_set_color(LED_L6, RGB_OFFBLUE);
            rgb_matrix_set_color(LED_CAPS, RGB_OFFBLUE);
        }
        break;

        // _GAMEMODE mode RGB
    case _GAMEMODE:
        rgb_matrix_set_color(LED_LWIN, RGB_RED); //light up Winkey red when disabled
        rgb_matrix_set_color(LED_W, RGB_CHARTREUSE); //light up gaming keys with WSAD higlighted
        rgb_matrix_set_color(LED_S, RGB_CHARTREUSE);
        rgb_matrix_set_color(LED_A, RGB_CHARTREUSE);
        rgb_matrix_set_color(LED_D, RGB_CHARTREUSE);
        rgb_matrix_set_color(LED_Q, RGB_ORANGE2);
        rgb_matrix_set_color(LED_E, RGB_ORANGE2);
        rgb_matrix_set_color(LED_R, RGB_ORANGE2);
        rgb_matrix_set_color(LED_TAB, RGB_ORANGE2);
        rgb_matrix_set_color(LED_F, RGB_ORANGE2);
        rgb_matrix_set_color(LED_Z, RGB_ORANGE2);
        rgb_matrix_set_color(LED_X, RGB_ORANGE2);
        rgb_matrix_set_color(LED_C, RGB_ORANGE2);
        rgb_matrix_set_color(LED_V, RGB_ORANGE2);
        rgb_matrix_set_color(LED_SPC, RGB_ORANGE2);
        rgb_matrix_set_color(LED_LCTL, RGB_ORANGE2);
        rgb_matrix_set_color(LED_LSFT, RGB_ORANGE2);
        break;

        // Colemak layer RGB
        #ifdef COLEMAK_LAYER_ENABLE
    case _COLEMAK:
        for (uint8_t i = 0; i < ARRAYSIZE(LED_SIDE_RIGHT); i++) {
            rgb_matrix_set_color(LED_SIDE_RIGHT[i], RGB_MAGENTA);
            rgb_matrix_set_color(LED_SIDE_LEFT[i], RGB_MAGENTA);
        }
        break;
        #endif

        break;
    }
}
#endif

void keyboard_post_init_keymap(void) {
    // keyboard_post_init_user() moved to userspace
    #ifdef RGB_MATRIX_ENABLE
    activate_rgb_nightmode(false); // Set to true if you want to startup in nightmode, otherwise use Fn + Z to toggle
    #endif
}