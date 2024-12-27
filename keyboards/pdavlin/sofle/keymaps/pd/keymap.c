
/* Copyright 2021 Dane Evans
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
// SOFLE RGB
#include <stdio.h>

#include QMK_KEYBOARD_H

#define INDICATOR_BRIGHTNESS 70

#define HSV_OVERRIDE_HELP(h, s, v, Override) h, s, Override
#define HSV_OVERRIDE(hsv, Override) HSV_OVERRIDE_HELP(hsv, Override)

// Light combinations
// notes on lights: underglow is 0-6, thumb keys are 7-8, then sequentially snakes up and down from there by column up to 34
// in order to set lights on non-master keyboard half, add 35
#define SET_NUMPAD(hsv)  \
    {35 + 13, 8, hsv}, { \
        35 + 23, 3, hsv  \
    }
#define SET_NUMROW(hsv)                                                                                                \
    {11, 1, hsv}, {12, 1, hsv}, {21, 2, hsv}, {30, 2, hsv}, {35 + 11, 1, hsv}, {35 + 12, 1, hsv}, {35 + 21, 2, hsv}, { \
        35 + 30, 2, hsv                                                                                                \
    }

// #define SET_LAYER_ID(hsv) {0, 6, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, {6, 2, hsv}, {16, 2, hsv}, {26, 1, hsv}, {35 + 0, 6, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, {35 + 6, 2, hsv}, {35 + 16, 2, hsv}, { 35 + 26, 1, hsv }

#define SET_LAYER_ID(hsv)                                       \
    {0, 6, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS)}, {     \
        35 + 0, 6, HSV_OVERRIDE_HELP(hsv, INDICATOR_BRIGHTNESS) \
    }

#define SET_ESDF(hsv)          \
    {14, 1, hsv}, {19, 2, hsv}, { \
        24, 1, hsv                \
    }

enum sofle_layers { _DEFAULTS = 0, _QWERTY = 0, _GAMING, _LOWER, _RAISE, _ADJUST, _NUMPAD, _SWITCH };

enum custom_keycodes { KC_QWERTY = SAFE_RANGE, KC_LOWER, KC_RAISE, KC_ADJUST, KC_D_MUTE };

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /*
     * QWERTY
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | LCTR |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
     * |------+------+------+------+------+------| MUTE  |    |DISCORD|------+------+------+------+------+------|
     * |Lshift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |LShift|
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | OS   | Lalt | LCTR | LOWER| /Space  /       \Enter \  |RAISE | RCTR | Ralt | RCTR |
     *            |      |      |      |      |/       /         \      \ |      |      |      |      |
     *            `----------------------------------'           '------''---------------------------'
     */
    [_QWERTY] = LAYOUT(
        //,------------------------------------------------.                    ,---------------------------------------------------.
           KC_ESC,  KC_1,   KC_2,    KC_3,   KC_4,    KC_5,            LT(_SWITCH, KC_6), KC_7,   KC_8,    KC_9,     KC_0,   KC_GRV,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        LT(_NUMPAD, KC_TAB), KC_Q, KC_W, KC_E, KC_R, KC_T,                        KC_Y,   KC_U,    KC_I,    KC_O,    KC_P,   KC_BSPC,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
          KC_LCTL, KC_A,   KC_S,     KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
          KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B, KC_MUTE,  KC_D_MUTE, KC_N,    KC_M,   KC_COMM, KC_DOT, KC_SLSH,  KC_LSFT,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                        KC_LGUI, KC_LALT, KC_LCTL, KC_LOWER, KC_SPC,     KC_ENT, KC_RAISE, KC_RCTL, KC_RALT, KC_RGUI
        //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
        ),

        /*
         * GAMING
         * ,-----------------------------------------.                    ,-----------------------------------------.
         * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
         * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
         * | TAB  |   Q  |   W  |   E  |   R  |   T  |                    |   Y  |   U  |   I  |   O  |   P  | Bspc |
         * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
         * | LCTR |   A  |   S  |   D  |   F  |   G  |-------.    ,-------|   H  |   J  |   K  |   L  |   ;  |  '   |
         * |------+------+------+------+------+------| MUTE  |    |DISCORD|------+------+------+------+------+------|
         * |Lshift|   Z  |   X  |   C  |   V  |   B  |-------|    |-------|   N  |   M  |   ,  |   .  |   /  |LShift|
         * `-----------------------------------------/       /     \      \-----------------------------------------'
         *            | Lalt | WIN  |  OS  | Space| /ScrLk  /       \Enter \  |RAISE |  OS  | Ralt | RCTR |
         *            |      |      |      |      |/       /         \      \ |      |      |      |      |
         *            `----------------------------------'           '------''---------------------------'
         */
    [_GAMING] = LAYOUT(
        //,------------------------------------------------.                    ,---------------------------------------------------.
           KC_ESC,  KC_1,   KC_2,    KC_3,   KC_4,    KC_5,            LT(_SWITCH, KC_6), KC_7,    KC_8,    KC_9,     KC_0,  KC_GRV,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
           KC_TAB,  KC_Q,   KC_W,    KC_E,   KC_R,    KC_T,                      KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,   KC_BSPC,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
          KC_LCTL, KC_A,   KC_S,     KC_D,    KC_F,   KC_G,                      KC_H,    KC_J,    KC_K,    KC_L,   KC_SCLN, KC_QUOT,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
          KC_LSFT, KC_Z,    KC_X,    KC_C,    KC_V,   KC_B, KC_MUTE,  KC_D_MUTE, KC_N,    KC_M,   KC_COMM, KC_DOT, KC_SLSH,  KC_LSFT,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                        KC_LGUI, KC_LALT, KC_LCTL, KC_SPC, KC_SCRL,     KC_ENT, KC_RAISE, KC_RCTL, KC_RALT, KC_RGUI
        //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
        ),

    /* LOWER
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | trans|  F1  |  F2  |  F3  |  F4  |  F5  |                    |  F6  |  F7  |  F8  |  F9  | F10  | F11  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |  `   |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | F12  |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | trans|   !  |   @  |   #  |   $  |   %  |-------.    ,-------|   ^  |   &  |   *  |   (  |   )  |   |  |
     * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
     * | trans|  =   |  -   |  +   |   {  |   }  |-------|    |-------|   [  |   ]  |   ;  |   :  |   \  | Shift|
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | GUI  | LAlt | LCTR | LOWER| /Space  /       \Enter \  |RAISE | RCTR | RAlt |  OS  |
     *            |      |      |      |      |/       /         \      \ |      |      |      |      |
     *            `----------------------------------'           '------''---------------------------'
     */
    [_LOWER] = LAYOUT(
        //,------------------------------------------------.                    ,---------------------------------------------------.
          _______, KC_F1,  KC_F2,    KC_F3,  KC_F4,  KC_F5,                      KC_F6,   KC_F7,   KC_F8,  KC_F9,   KC_F10,  KC_F11,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
           KC_GRV, KC_1,    KC_2,    KC_3,    KC_4,   KC_5,                     KC_HOME, KC_PGUP, KC_UP,   KC_PGDN,  KC_0,   KC_F12,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
         _______, XXXXXXX,XXXXXXX, XXXXXXX, KC_WH_U,KC_PGUP,                    KC_END,  KC_LEFT, KC_DOWN, KC_RGHT, XXXXXXX, KC_DEL,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
         _______, XXXXXXX,XXXXXXX, XXXXXXX, KC_WH_D,KC_PGDN, _______, _______,  XXXXXXX, XXXXXXX,XXXXXXX, XXXXXXX, XXXXXXX, _______,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                        _______, _______, _______, _______, _______,     _______, _______, _______, _______, _______
        //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
        ),
    /* RAISE
     * ,----------------------------------------.                    ,-----------------------------------------.
     * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |  `   |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | Tab  | Ins  | Pscr | Menu |      |      |                    |  ^   |   &  |   *  |   (  |   )  | Bspc |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | LCTR | LAt  | LCtl |LShift|      | Caps |-------.    ,-------|   -  |   =  |   {  |   }  |   |  |   `  |
     * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
     * |LShift| Undo |  Cut | Copy | Paste|      |-------|    |-------|   _  |   +  |   [  |   ]  |   \   |  ~  |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
     *            |      |      |      |      |/       /         \      \ |      |      |      |      |
     *            `----------------------------------'           '------''---------------------------'
     */
    [_RAISE] = LAYOUT(
        //,------------------------------------------------.                    ,---------------------------------------------------.
        _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        _______, KC_INS, KC_PSCR, KC_APP, XXXXXXX, XXXXXXX,                     KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, KC_BSPC,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        _______, KC_LALT, KC_LCTL, KC_LSFT, XXXXXXX, KC_CAPS,                   KC_MINS, KC_EQL, KC_LCBR, KC_RCBR,  KC_PIPE, KC_GRV,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        _______, KC_UNDO, KC_CUT, KC_COPY, KC_PASTE, XXXXXXX, _______, _______, KC_UNDS, KC_PLUS, KC_LBRC, KC_RBRC, KC_BSLS, KC_TILD,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                        _______, _______, _______, _______, _______,    _______, _______, _______, _______, _______
        //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
        ),
    /* ADJUST
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | QK_BOOT|    |      |      |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |UG_TOGG|hue^ |sat ^ | bri ^|      |      |-------.   ,-------|desk <|      |      |desk >|      |      |
     * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
     * | mode | hue dn|sat d|bri dn|      |      |-------|    |-------|      | PREV | PLAY | NEXT |      |      |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | LGUI | LAlt | LCTR |LOWER | /Enter  /       \Space \  |RAISE | RCTR | RAlt | RGUI |
     *            |      |      |      |      |/       /         \      \ |      |      |      |      |
     *            `----------------------------------'           '------''---------------------------'
     */
    [_ADJUST] = LAYOUT(
        //,------------------------------------------------.                    ,---------------------------------------------------.
        EE_CLR,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        UG_TOGG, UG_HUEU, UG_SATU, UG_VALU, XXXXXXX, XXXXXXX,              C(G(KC_LEFT)), XXXXXXX, XXXXXXX, C(G(KC_RGHT)), XXXXXXX, XXXXXXX,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        UG_NEXT, UG_HUED, UG_SATD, UG_VALD, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT, XXXXXXX, XXXXXXX,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                       _______, _______, _______, _______, _______,      _______, _______, _______, _______, _______
        //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
        ),
    /* NUMPAD
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | trans|      |      |      |      |      |                    |      |NumLck|      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |  `   |      |      |      |      |      |                    |   ^  |   7  |   8  |   9  |   *  |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | trans|      |      |      |      |      |-------.    ,-------|   -  |   4  |   5  |   6  |   =  |   |  |
     * |------+------+------+------+------+------|  MUTE |    |       |------+------+------+------+------+------|
     * | trans|      |      |      |      |      |-------|    |-------|   +  |   1  |   2  |   3  |   \  | Shift|
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            | Bspc | WIN  |LOWER | Enter| /Space  /       \Enter \  |SPACE | 0    |  .   | RAlt |
     *            |      |      |      |      |/       /         \      \ |      |      |      |      |
     *            `----------------------------------'           '------''---------------------------'
     */
    [_NUMPAD] = LAYOUT(
        //,------------------------------------------------.                    ,---------------------------------------------------.
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   _______, KC_NUM, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_CIRC,  KC_P7,  KC_P8,   KC_P9,   KC_ASTR, XXXXXXX,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   KC_MINS,  KC_P4,  KC_P5,   KC_P6,   KC_EQL,  KC_PIPE,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______, _______, KC_PLUS,  KC_P1,  KC_P2,   KC_P3,   KC_SLSH, _______,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                  _______, OSM(MOD_MEH), _______, _______, _______,      _______, _______, KC_P0, KC_PDOT, _______
        //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/
        ),

    /* SWITCH
     * ,-----------------------------------------.                    ,-----------------------------------------.
     * | ESC  |      |      |      |      |      |                    |      |      |      |      |      |      |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * | qwer | game | low  | raise| adj  |numpad|                    |      |      |      |      |      |QK_BOOT |
     * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
     * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |EE_CLR|
     * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
     * | SLEEP|      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
     * `-----------------------------------------/       /     \      \-----------------------------------------'
     *            |      |      |      |      | /       /       \      \  |      |      |      |      |
     *            |      |      |      |      |/       /         \      \ |      |      |      |      |
     *            `----------------------------------'           '------''---------------------------'
     */
    // layer switcher
    [_SWITCH] = LAYOUT(
        //,------------------------------------------------.                    ,---------------------------------------------------.
        _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
            TO(0), TO(1),  TO(2),   TO(3),   TO(4),   TO(5),                    XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, QK_BOOT,
        //|------+-------+--------+--------+--------+------|                   |--------+-------+--------+--------+--------+---------|
        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, EE_CLR,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
        KC_SYSTEM_SLEEP, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
        //|------+-------+--------+--------+--------+------|  ===  |   |  ===  |--------+-------+--------+--------+--------+---------|
                       XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,      XXXXXXX, XXXXXXX,  XXXXXXX, XXXXXXX, XXXXXXX
        //            \--------+--------+--------+---------+-------|   |--------+---------+--------+---------+-------/

        ),
};

#ifdef RGBLIGHT_ENABLE
char layer_state_str[70];
// Now define the array of layers. Later layers take precedence

// QWERTY,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_qwerty_lights[]    = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_RED)

   );
const rgblight_segment_t PROGMEM layer_gaming_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_MAGENTA), SET_ESDF(HSV_MAGENTA));

// _NUM,
// Light on outer column and underglow
const rgblight_segment_t PROGMEM layer_num_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_TEAL)

);
// _SYMBOL,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_symbol_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_BLUE)

);
// _COMMAND,
// Light on inner column and underglow
const rgblight_segment_t PROGMEM layer_command_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_PURPLE));

//_NUMPAD
const rgblight_segment_t PROGMEM layer_numpad_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_ORANGE), SET_NUMPAD(HSV_BLUE));
// _SWITCHER   // light up top row
const rgblight_segment_t PROGMEM layer_switcher_lights[] = RGBLIGHT_LAYER_SEGMENTS(SET_LAYER_ID(HSV_GREEN), SET_NUMROW(HSV_GREEN));

const rgblight_segment_t *const PROGMEM my_rgb_layers[] = RGBLIGHT_LAYERS_LIST(

    layer_qwerty_lights,
    layer_num_lights, // overrides layer 1
    layer_symbol_lights, layer_command_lights, layer_numpad_lights,
    layer_gaming_lights,
    layer_switcher_lights // Overrides other layers
    );

layer_state_t layer_state_set_user(layer_state_t state) {
    rgblight_set_layer_state(0, layer_state_cmp(state, _DEFAULTS) && layer_state_cmp(default_layer_state, _QWERTY));

    rgblight_set_layer_state(1, layer_state_cmp(state, _LOWER));
    rgblight_set_layer_state(2, layer_state_cmp(state, _RAISE));
    rgblight_set_layer_state(3, layer_state_cmp(state, _ADJUST));
    rgblight_set_layer_state(4, layer_state_cmp(state, _NUMPAD));
    rgblight_set_layer_state(5, layer_state_cmp(state, _GAMING));
    rgblight_set_layer_state(6, layer_state_cmp(state, _SWITCH));
    return state;
}
void keyboard_post_init_user(void) {
    // Enable the LED layers
    rgblight_layers = my_rgb_layers;

    rgblight_mode(10); // haven't found a way to set this in a more useful way
}
#endif

#ifdef OLED_ENABLE
    #include "luna.c" //OLED code for Luna, original code by Hellsingcoder and adapted by Jackasaur.
#endif

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case KC_QWERTY:
            if (record->event.pressed) {
                set_single_persistent_default_layer(_QWERTY);
            }
            return false;
        case KC_LOWER:
            if (record->event.pressed) {
                layer_on(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_LOWER);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_RAISE:
            if (record->event.pressed) {
                layer_on(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            } else {
                layer_off(_RAISE);
                update_tri_layer(_LOWER, _RAISE, _ADJUST);
            }
            return false;
        case KC_ADJUST:
            if (record->event.pressed) {
                layer_on(_ADJUST);
            } else {
                layer_off(_ADJUST);
            }
            return false;
        case KC_D_MUTE:
            if (record->event.pressed) {
                register_mods(mod_config(MOD_MEH));
                register_code(KC_UP);
            } else {
                unregister_mods(mod_config(MOD_MEH));
                unregister_code(KC_UP);
            }
        case KC_LCTL:
        case KC_RCTL:
            if (record->event.pressed) {
                isSneaking = true;
            } else {
                isSneaking = false;
            }
            break;
        case KC_SPC:
            if (record->event.pressed) {
                isJumping  = true;
                showedJump = false;
            } else {
                isJumping = false;
            }
            break;
    }
    return true;
}

#ifdef ENCODER_ENABLE

bool encoder_update_user(uint8_t index, bool clockwise) {
    if (index == 0) {
        if (clockwise) {
            tap_code(KC_VOLU);
        } else {
            tap_code(KC_VOLD);
        }
    } else if (index == 1) {
        if (clockwise) {
            tap_code(MS_WHLD);

        } else {
            tap_code(MS_WHLU);
        }
    }
    return false;
}

#endif
