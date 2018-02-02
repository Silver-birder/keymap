#include "ergodox.h"
#include "debug.h"
#include "action_layer.h"

#define BASE 0 // default layer
#define SYMB 1 // symbols
#define MDIA 2 // media keys

#define JA_CLON KC_QUOT  // : and +
#define JA_AT   KC_LBRC  // @ and `
#define JA_HAT  KC_EQL   // ^ and ~
#define JA_ENUN KC_RO    // \ and _ (EN mark and UNder score)
#define JA_ENVL KC_JYEN  // \ and | (EN mark and Vertical Line)
#define JA_LBRC KC_RBRC  // [ and {
#define JA_RBRC KC_BSLS  // ] and }

// Custom Aliases
// ref: qmk_firmware/quantum/keymap_common.h
#define A(kc)     LALT(kc)
#define C(kc)     LCTL(kc)
#define G(kc)     LGUI(kc)
// HYPR(kc) = Ctrl + Shift + Alt + Gui + kc
// MEH(kc)  = Ctrl + Shift + Alt       + kc
// LCAG(kc) = Ctrl         + Alt + Gui + kc
#define C_S(kc)   kc | 0x0100 | 0x0200 // `Ctrl + Shift + kc`
#define C_A(kc)   kc | 0x0100 | 0x0400 // `Ctrl + Alt +kc`
#define G_S(kc)   kc | 0x0100 | 0x0800 | 0x0200 // `Ctrl + Gui  + Shift + kc`
#define G_A(kc)   kc | 0x0800 | 0x0400 // `Gui  + Alt   + kc`
#define G_S_T(kc) MT(0x8 | 0x2, kc)   // `Gui + Shift` or kc
#define G_A_T(kc) MT(0x8 | 0x4, kc)   // `Gui + Alt`   or kc

enum {
    ALFRED_DASH = 1,
	PASS = 2
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
/* Keymap 0: Basic layer
 *
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * | ESC    |   1  |   2  |   3  |   4  |   5  |      |           |      |   6  |   7  |   8  |   9  |   0  |   -    |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * | Tab    |   Q  |   W  |   E  |   R  |   T  |   [  |           |  ]   |   Y  |   U  |   I  |   O  |   P  |   @    |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * | L2     |   A  |   S  |   D  |   F  |   G  |------|           |------|   H  |   J  |   K  |   L  |   ;  |:  / L1 |
 * |--------+------+------+------+------+------| KANA |           | EISU |------+------+------+------+------+--------|
 * | LShft  |   Z  |   X  |   C  |   V  |   B  |      |           |      |   N  |   M  |   ,  |   .  |   /  |_ /RShft|
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   | LCtrl|  Cmd | LAlt | Home |  End |                                       |   ¥  |   ^  | RAlt | Cmd  |  RCtrl |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |C_S   | C_A  |       | APP  |DELETE|
 *                                 ,------|------|------|       |------+--------+------.
 *                                 |      |      |  L2  |       |  L2  |        |      |
 *                                 | Space|Backsp|------|       |------|  Tab   |Enter |
 *                                 |      |ace   |  L1  |       |  L1  |        |      |
 *                                 `--------------------'       `----------------------'
 */
// If it accepts an argument (i.e, is a function), it doesn't need KC_.
// Otherwise, it needs KC_*
[BASE] = KEYMAP(  // layer 0 : default
        // left hand
        KC_ESC,         KC_1,         KC_2,        KC_3,    KC_4,              KC_5,              KC_TRNS,
        KC_TAB,          KC_Q,         KC_W,        KC_E,    KC_R,              KC_T,              JA_LBRC,
        MO(MDIA),        KC_A,         KC_S,        KC_D,    KC_F,              KC_G,
        KC_LSFT,         KC_Z,         KC_X,        KC_C,    KC_V,              KC_B,              KC_HENK,
        KC_LCTRL,        KC_LGUI,      KC_LALT,     KC_HOME, KC_END,
                                                    C_S(KC_NO),C_A(KC_NO),
                                                             MO(MDIA),
                                       KC_SPC,      KC_BSPC, MO(SYMB),
        // right hand
         KC_TRNS,        KC_6,         KC_7,        KC_8,    KC_9,              KC_0,              KC_MINS,
         JA_RBRC,        KC_Y,         KC_U,        KC_I,    KC_O,              KC_P,              JA_AT,
                         KC_H,         KC_J,        KC_K,    KC_L,              KC_SCLN,           LT(SYMB,JA_CLON),
         KC_MHEN,        KC_N,         KC_M,        KC_COMM, KC_DOT,            KC_SLSH,           SFT_T(S(JA_ENUN)),
                                       KC_JYEN,     JA_HAT,  KC_LALT,           KC_RGUI,           KC_RCTRL,
         KC_APP,        KC_DELETE,
         MO(MDIA),
         MO(SYMB),       KC_TAB,       KC_ENT
    ),
/* Keymap 1: Symbol Layer
 *
 *  - CmdShF3 = Take a screenshot of part of your screen
 *  - CtlShI  = Developper Tool(Chrome)
 *  - CmdPSCR - screenshot
 *  - CtlU    = View Source(Chrome)
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |      |      |      |      |      |      |           |      |      |      |      |  %   |  /   |        |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |   Up |   7  |   8  |   9  |  *   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |CdPSCR| CtlU |CtlShI|      |------|           |------| Down |   4  |   5  |   6  |  -   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |Dash  |      |      |      |      |      |           |      |      |   1  |   2  |   3  |  +   |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |   0  |      |    . |  =   |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |      |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 |      |      |------|       |------|      |      |
 *                                 |      |      |      |       |      |      |      |
 *                                 `--------------------'       `--------------------'
 */
// SYMBOLS
[SYMB] = KEYMAP(
       // left hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,    KC_TRNS,    KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,    KC_TRNS,    KC_TRNS,
       KC_TRNS, KC_TRNS, G(KC_PSCR),C(KC_U),     C_S(KC_I),    KC_TRNS,
       KC_TRNS, M(ALFRED_DASH),   KC_TRNS,     KC_TRNS,    KC_TRNS,    KC_TRNS,    KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     KC_TRNS,
                                  KC_TRNS,     KC_TRNS,
                                               KC_TRNS,
                         KC_TRNS, KC_TRNS,     KC_TRNS,
       // right hand
       KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,     S(KC_5),    KC_SLSH,    KC_TRNS,
       KC_TRNS, KC_UP,   KC_7,    KC_8,        KC_9,       S(KC_QUOT), KC_TRNS,
                KC_DOWN, KC_4,    KC_5,        KC_6,       KC_MINS,    KC_TRNS,
       KC_TRNS, KC_TRNS, KC_1,    KC_2,        KC_3,       S(KC_SCLN), KC_TRNS,
                         KC_0,    KC_TRNS,     KC_DOT,     S(KC_MINS), KC_TRNS,
       KC_TRNS, KC_TRNS,
       KC_TRNS,
       KC_TRNS, KC_TRNS, KC_TRNS
),
/* Keymap 2: Media and mouse keys
 *
 * ,--------------------------------------------------.           ,--------------------------------------------------.
 * |        |  F1  |  F2  |  F3  |  F4  |  F5  | RESET|           |      |  F6  |  F7  |  F8  |  F9  | F10  |  F11   |
 * |--------+------+------+------+------+-------------|           |------+------+------+------+------+------+--------|
 * |        |      |      | MsUp |      | MwUp |      |           |      | PgUp |      |  Up  |      |HOME  |  F12   |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |MsLeft|MsDown|MsRght|MwDown|------|           |------| PgDn | Left | Down | Right|END   |        |
 * |--------+------+------+------+------+------|      |           |      |------+------+------+------+------+--------|
 * |        |      |      |      |      |      |      |           |      |      |      |      |      |      |        |
 * `--------+------+------+------+------+-------------'           `-------------+------+------+------+------+--------'
 *   |      |      |      |      |      |                                       |      |      |      |      |      |
 *   `----------------------------------'                                       `----------------------------------'
 *                                        ,-------------.       ,-------------.
 *                                        |      |      |       |      |  ACL |
 *                                 ,------|------|------|       |------+------+------.
 *                                 |      |      |      |       |      |      |      |
 *                                 | Lclk | Rclk |------|       |------| Back |Forwar|
 *                                 |      |      |      |       |      |      |d     |
 *                                 `--------------------'       `--------------------'
 */
// MEDIA AND MOUSE
[MDIA] = KEYMAP(
       KC_TRNS,        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   RESET,
       KC_TRNS,        KC_TRNS, KC_TRNS, KC_MS_U, KC_TRNS, KC_WH_U, KC_TRNS,
       KC_TRNS,        KC_TRNS, KC_MS_L, KC_MS_D, KC_MS_R, KC_WH_D,
       KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                         KC_TRNS, KC_TRNS,
                                                  KC_TRNS,
                                KC_BTN1, KC_BTN2, KC_TRNS,
    // right hand
       KC_TRNS,        KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,
       KC_TRNS,        KC_PGUP, KC_TRNS, KC_UP,   KC_TRNS, KC_HOME, KC_F12,
                       KC_PGDN, KC_LEFT, KC_DOWN, KC_RGHT, KC_END, KC_TRNS,
       KC_TRNS,        KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
                                KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS, KC_TRNS,
       KC_TRNS,       KC_ACL0,
       KC_TRNS,
       KC_TRNS,       A(KC_LEFT),A(KC_RGHT)
),
};

const uint16_t PROGMEM fn_actions[] = {
    //[1] = ACTION_LAYER_TAP_TOGGLE(SYMB)                // FN1 - Momentary Layer 1 (Symbols)
};

const macro_t *action_get_macro(keyrecord_t *record, uint8_t id, uint8_t opt){
  // MACRODOWN only works in this function
      switch(id) {
        case 0:
        if (record->event.pressed) {
          register_code(KC_RSFT);
        } else {
          unregister_code(KC_RSFT);
        }
        break;
      case ALFRED_DASH:
        if (record->event.pressed) {
          return MACRO( D(LALT), D(SPC), END );
        }
        break;
      case PASS:
        if (record->event.pressed) {
          return MACRO(T(S),T(I),T(L),T(V),T(E),T(R),T(B),T(I),T(R),T(D),T(E),T(R),END);
        }
        break;
      }
    return MACRO_NONE;
};

// Runs just one time when the keyboard initializes.
void matrix_init_user(void) {

};

void light_led_on_pressed(void) {

    ergodox_right_led_3_off();

    for (uint8_t row = 0; row < MATRIX_ROWS; row++) {
      for (uint8_t col = 0; col < MATRIX_COLS; col++) {
        if (matrix_is_on(row, col)) {

          action_t action = layer_switch_get_action((keypos_t){ .row = row, .col = col });

          if(IS_MOD(action.code)) {
            ergodox_right_led_3_on();
            break;
          }
        }
      }
    }
}

// Runs constantly in the background, in a loop.
void matrix_scan_user(void) {

    uint8_t layer = biton32(layer_state);

    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();
    switch (layer) {
      // TODO: Make this relevant to the ErgoDox EZ.
        case 1:
            ergodox_right_led_1_on();
            break;
        case 2:
            ergodox_right_led_2_on();
            break;
        default:
            // none
            break;
    }

    light_led_on_pressed();

};
