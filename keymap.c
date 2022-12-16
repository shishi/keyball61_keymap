/*
Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

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

#include QMK_KEYBOARD_H

#include "quantum.h"

typedef struct {
    bool is_press_action;
    int state;
} tap;

enum {
    SINGLE_TAP = 1,
    SINGLE_HOLD = 2,
    DOUBLE_TAP = 3,
    DOUBLE_HOLD = 4,
    DOUBLE_SINGLE_TAP = 5, //send two single taps
    TRIPLE_TAP = 6,
    TRIPLE_HOLD = 7,
    TRIPLE_SINGLE_TAP = 8 //send three single taps
};

enum {
    TD_TRIPLE_BRACE_START = 0,
    TD_TRIPLE_BRACE_END,
    TD_B,
    TD_C,
    TD_E,
    TD_G,
    TD_H,
    TD_I,
    TD_N,
    TD_R,
    TD_T,
    TD_V,
    TD_X,
    TD_Y,
    TD_Z
};

void triple_brace_start(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 1){
        register_code(KC_LSFT);
        register_code(KC_9);
        unregister_code(KC_9);
        unregister_code(KC_LSFT);
    }else if(state->count == 2){
        register_code(KC_LBRC);
        unregister_code(KC_LBRC);
    }else if(state->count == 3){
        register_code(KC_LSFT);
        register_code(KC_LBRC);
        unregister_code(KC_LBRC);
        unregister_code(KC_LSFT);
    }
    reset_tap_dance (state);
}

void triple_brace_end(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 1){
        register_code(KC_LSFT);
        register_code(KC_0);
        unregister_code(KC_0);
        unregister_code(KC_LSFT);
    }else if(state->count == 2){
        register_code(KC_RBRC);
        unregister_code(KC_RBRC);
    }else if(state->count == 3){
        register_code(KC_LSFT);
        register_code(KC_RBRC);
        unregister_code(KC_RBRC);
        unregister_code(KC_LSFT);
    }
    reset_tap_dance (state);
}

int cur_dance (qk_tap_dance_state_t *state);

//for the x tap dance. Put it here so it can be used in any keymap
void b_finished (qk_tap_dance_state_t *state, void *user_data);
void b_reset (qk_tap_dance_state_t *state, void *user_data);
void c_finished (qk_tap_dance_state_t *state, void *user_data);
void c_reset (qk_tap_dance_state_t *state, void *user_data);
void e_finished (qk_tap_dance_state_t *state, void *user_data);
void e_reset (qk_tap_dance_state_t *state, void *user_data);
void g_finished (qk_tap_dance_state_t *state, void *user_data);
void g_reset (qk_tap_dance_state_t *state, void *user_data);
void h_finished (qk_tap_dance_state_t *state, void *user_data);
void h_reset (qk_tap_dance_state_t *state, void *user_data);
void i_finished (qk_tap_dance_state_t *state, void *user_data);
void i_reset (qk_tap_dance_state_t *state, void *user_data);
void n_finished (qk_tap_dance_state_t *state, void *user_data);
void n_reset (qk_tap_dance_state_t *state, void *user_data);
void r_finished (qk_tap_dance_state_t *state, void *user_data);
void r_reset (qk_tap_dance_state_t *state, void *user_data);
void t_finished (qk_tap_dance_state_t *state, void *user_data);
void t_reset (qk_tap_dance_state_t *state, void *user_data);
void v_finished (qk_tap_dance_state_t *state, void *user_data);
void v_reset (qk_tap_dance_state_t *state, void *user_data);
void x_finished (qk_tap_dance_state_t *state, void *user_data);
void x_reset (qk_tap_dance_state_t *state, void *user_data);
void y_finished (qk_tap_dance_state_t *state, void *user_data);
void y_reset (qk_tap_dance_state_t *state, void *user_data);
void z_finished (qk_tap_dance_state_t *state, void *user_data);
void z_reset (qk_tap_dance_state_t *state, void *user_data);

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    TO(2)    , KC_1         , KC_2         , KC_3         , KC_4         , KC_5         ,                                          KC_6          , KC_7         , KC_8         , KC_9         , KC_0            , TO(3)         ,
    TO(2)    , KC_Q         , KC_W         , TD(TD_E)     , TD(TD_R)     , TD(TD_T)     ,                                          TD(TD_Y)      , KC_U         , TD(TD_I)     , KC_O         , KC_P            , KC_GRV        ,
    KC_MINUS , LGUI_T(KC_A) , LALT_T(KC_S) , LSFT_T(KC_D) , LCTL_T(KC_F) , TD(TD_G)     ,                                          TD(TD_H)      , RCTL_T(KC_J) , RSFT_T(KC_K) , RALT_T(KC_L) , RGUI_T(KC_SCLN) , LT(1,KC_QUOT) ,
    KC_EQL   , TD(TD_Z)     , TD(TD_X)     , TD(TD_C)     , TD(TD_V)     , TD(TD_B)     , KC_LNG1      ,          KC_LNG2        , TD(TD_N)      , KC_M         , KC_COMM      , KC_DOT       , KC_SLSH         , LT(2,KC_BSLS) ,
    KC_MEH   , KC_APP       , XXXXXXX      , XXXXXXX      , LT(3,KC_ESC) , LT(2,KC_SPC) , LT(1,KC_TAB) ,          LT(1,KC_ENTER) , LT(2,KC_BSPC) , XXXXXXX      , XXXXXXX      , XXXXXXX      , KC_PSCR         , KC_MEH
  ),

  [1] = LAYOUT_universal(
    TO(0)   , XXXXXXX  , KC_PEQL , KC_PSLS , KC_PAST , KC_NUM  ,                                 XXXXXXX    , XXXXXXX    , XXXXXXX     , XXXXXXX , XXXXXXX , TO(0)   ,
    TO(0)   , XXXXXXX  , KC_P7   , KC_P8   , KC_P9   , KC_PMNS ,                                 XXXXXXX    , A(KC_LEFT) , A(KC_RIGHT) , XXXXXXX , XXXXXXX , TO(0)   ,
    XXXXXXX , XXXXXXX  , KC_P4   , KC_P5   , KC_P6   , KC_PPLS ,                                 C(KC_W)    , KC_BTN1    , KC_BTN3     , KC_BTN2 , XXXXXXX , XXXXXXX ,
    XXXXXXX , XXXXXXX  , KC_P1   , KC_P2   , KC_P3   , KC_PENT , XXXXXXX ,            XXXXXXX  , C(S(KC_T)) , KC_PGUP    , KC_PGDN     , XXXXXXX , XXXXXXX , XXXXXXX ,
    XXXXXXX , XXXXXXX  , KC_0    , KC_PDOT , KC_PCMM , XXXXXXX , XXXXXXX  ,           XXXXXXX  , KC_DEL     , XXXXXXX    , XXXXXXX     , XXXXXXX , XXXXXXX , XXXXXXX
  ),

  [2] = LAYOUT_universal(
    TO(0)   , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                 XXXXXXX , KC_INS   , KC_SCRL , XXXXXXX  , XXXXXXX , TO(0)   ,
    TO(0)   , KC_F1   , KC_F2   , KC_F3   , KC_F4   , XXXXXXX ,                                 XXXXXXX , KC_HOME  , KC_END  , XXXXXXX  , XXXXXXX , TO(0)   ,
    XXXXXXX , KC_F5   , KC_F6   , KC_F7   , KC_F8   , XXXXXXX ,                                 KC_LEFT , KC_DOWN  , KC_UP   , KC_RGHT  , XXXXXXX , XXXXXXX ,
    XXXXXXX , KC_F9   , KC_F10  , KC_F11  , KC_F12  , XXXXXXX , XXXXXXX  ,            XXXXXXX , XXXXXXX , KC_PGUP  , KC_PGDN , XXXXXXX  , XXXXXXX , XXXXXXX ,
    XXXXXXX , KC_F13  , KC_F14  , KC_F15  , KC_BSPC , KC_SPC  , KC_ENTER ,            XXXXXXX , KC_DEL  , XXXXXXX  , XXXXXXX , XXXXXXX  , XXXXXXX , XXXXXXX
  ),

  [3] = LAYOUT_universal(
    TO(0)   , XXXXXXX  , XXXXXXX , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                              XXXXXXX , XXXXXXX    , XXXXXXX    , XXXXXXX , XXXXXXX , TO(0)   ,
    TO(0)   , KBC_RST  , XXXXXXX , CPI_D1K  , CPI_I1K  , XXXXXXX  ,                              XXXXXXX , KC_LBRC    , KC_RBRC    , XXXXXXX , XXXXXXX , XXXXXXX ,
    XXXXXXX , KBC_SAVE , XXXXXXX , CPI_D100 , CPI_I100 , XXXXXXX  ,                              XXXXXXX , S(KC_9)    , S(KC_0)    , XXXXXXX , XXXXXXX , XXXXXXX ,
    XXXXXXX , XXXXXXX  , XXXXXXX , SCRL_DVI , SCRL_DVD , XXXXXXX  , RESET ,            EEP_RST , XXXXXXX , S(KC_LBRC) , S(KC_RBRC) , XXXXXXX , XXXXXXX , XXXXXXX ,
    RESET   , XXXXXXX  , XXXXXXX , XXXXXXX  , XXXXXXX  , KC_SPC   , XXXXXXX ,          XXXXXXX , KC_DEL  , XXXXXXX    , XXXXXXX    , XXXXXXX , XXXXXXX , XXXXXXX
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 2);
    return state;
}

#ifdef OLED_ENABLE

#include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
}
#endif

/* Return an integer that corresponds to what kind of tap dance should be executed.
 *
 * How to figure out tap dance state: interrupted and pressed.
 *
 * Interrupted: If the state of a dance dance is "interrupted", that means that another key has been hit
 *  under the tapping term. This is typically indicitive that you are trying to "tap" the key.
 *
 * Pressed: Whether or not the key is still being pressed. If this value is true, that means the tapping term
 *  has ended, but the key is still being pressed down. This generally means the key is being "held".
 *
 * One thing that is currenlty not possible with qmk software in regards to tap dance is to mimic the "permissive hold"
 *  feature. In general, advanced tap dances do not work well if they are used with commonly typed letters.
 *  For example "A". Tap dances are best used on non-letter keys that are not hit while typing letters.
 *
 * Good places to put an advanced tap dance:
 *  z,q,x,j,k,v,b, any function key, home/end, comma, semi-colon
 *
 * Criteria for "good placement" of a tap dance key:
 *  Not a key that is hit frequently in a sentence
 *  Not a key that is used frequently to double tap, for example 'tab' is often double tapped in a terminal, or
 *    in a web form. So 'tab' would be a poor choice for a tap dance.
 *  Letters used in common words as a double. For example 'p' in 'pepper'. If a tap dance function existed on the
 *    letter 'p', the word 'pepper' would be quite frustating to type.
 *
 * For the third point, there does exist the 'DOUBLE_SINGLE_TAP', however this is not fully tested
 *
 */
int cur_dance (qk_tap_dance_state_t *state) {
    if (state->count == 1) {
        if (state->interrupted || !state->pressed)  return SINGLE_TAP;
        //key has not been interrupted, but they key is still held. Means you want to send a 'HOLD'.
        else return SINGLE_HOLD;
    }
    else if (state->count == 2) {
        /*
        * DOUBLE_SINGLE_TAP is to distinguish between typing "pepper", and actually wanting a double tap
        * action when hitting 'pp'. Suggested use case for this return value is when you want to send two
        * keystrokes of the key, and not the 'double tap' action/macro.
        */
        if (state->interrupted) return DOUBLE_SINGLE_TAP;
        else if (state->pressed) return DOUBLE_HOLD;
        else return DOUBLE_TAP;
    }
    //Assumes no one is trying to type the same letter three times (at least not quickly).
    //If your tap dance key is 'KC_W', and you want to type "www." quickly - then you will need to add
    //an exception here to return a 'TRIPLE_SINGLE_TAP', and define that enum just like 'DOUBLE_SINGLE_TAP'
    else if (state->count == 3) {
        if (state->interrupted) return TRIPLE_SINGLE_TAP;
        else if (state->pressed) return TRIPLE_HOLD;
        else return TRIPLE_TAP;
    }
    else return 99; //magic number. At some point this method will expand to work for more presses
};

//instanalize an instance of 'tap' for the 'x' tap dance.
static tap btap_state = {
    .is_press_action = true,
    .state = 0
};
static tap ctap_state = {
    .is_press_action = true,
    .state = 0
};
static tap etap_state = {
    .is_press_action = true,
    .state = 0
};
static tap gtap_state = {
    .is_press_action = true,
    .state = 0
};
static tap htap_state = {
    .is_press_action = true,
    .state = 0
};
static tap itap_state = {
    .is_press_action = true,
    .state = 0
};
static tap ntap_state = {
    .is_press_action = true,
    .state = 0
};
static tap rtap_state = {
    .is_press_action = true,
    .state = 0
};
static tap ttap_state = {
    .is_press_action = true,
    .state = 0
};
static tap vtap_state = {
    .is_press_action = true,
    .state = 0
};
static tap xtap_state = {
    .is_press_action = true,
    .state = 0
};
static tap ytap_state = {
    .is_press_action = true,
    .state = 0
};
static tap ztap_state = {
    .is_press_action = true,
    .state = 0
};

void b_finished (qk_tap_dance_state_t *state, void *user_data) {
    btap_state.state = cur_dance(state);
    switch (btap_state.state) {
        case SINGLE_TAP: register_code(KC_B); break;
        case SINGLE_HOLD: register_code(KC_LSFT); register_code(KC_LBRC); break;
        case DOUBLE_TAP: register_code(KC_B); unregister_code(KC_B); register_code(KC_B); break;
        case DOUBLE_HOLD: register_code(KC_B); break;
        case DOUBLE_SINGLE_TAP: register_code(KC_B); unregister_code(KC_B); register_code(KC_B); break;
        //Last case is for fast typing. Assuming your key is `f`:
        //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TRIPLE_TAP: register_code(KC_B); unregister_code(KC_B); register_code(KC_B); unregister_code(KC_B); register_code(KC_B); break;
        case TRIPLE_HOLD: register_code(KC_B); break;
        case TRIPLE_SINGLE_TAP: register_code(KC_B); unregister_code(KC_B); register_code(KC_B); unregister_code(KC_B); register_code(KC_B);
    }
};
void b_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (btap_state.state) {
        case SINGLE_TAP: unregister_code(KC_B); break;
        case SINGLE_HOLD: unregister_code(KC_LSFT);unregister_code(KC_LBRC); break;
        case DOUBLE_TAP: unregister_code(KC_B); break;
        case DOUBLE_HOLD: unregister_code(KC_B); break;
        case DOUBLE_SINGLE_TAP: unregister_code(KC_B); break;
        case TRIPLE_TAP: unregister_code(KC_B); break;
        case TRIPLE_HOLD: unregister_code(KC_B); break;
        case TRIPLE_SINGLE_TAP: unregister_code(KC_B);
    }
    btap_state.state = 0;
};

void c_finished (qk_tap_dance_state_t *state, void *user_data) {
    ctap_state.state = cur_dance(state);
    switch (ctap_state.state) {
        case SINGLE_TAP: register_code(KC_C); break;
        case SINGLE_HOLD: register_code(KC_LCTRL); register_code(KC_C); break;
        case DOUBLE_TAP: register_code(KC_C); unregister_code(KC_C); register_code(KC_C); break;
        case DOUBLE_HOLD: register_code(KC_C); break;
        case DOUBLE_SINGLE_TAP: register_code(KC_C); unregister_code(KC_C); register_code(KC_C); break;
        //Last case is for fast typing. Assuming your key is `f`:
        //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TRIPLE_TAP: register_code(KC_C); unregister_code(KC_C); register_code(KC_C); unregister_code(KC_C); register_code(KC_C); break;
        case TRIPLE_HOLD: register_code(KC_C); break;
        case TRIPLE_SINGLE_TAP: register_code(KC_C); unregister_code(KC_C); register_code(KC_C); unregister_code(KC_C); register_code(KC_C);
    }
};
void c_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (ctap_state.state) {
        case SINGLE_TAP: unregister_code(KC_C); break;
        case SINGLE_HOLD: unregister_code(KC_LCTRL); unregister_code(KC_C); break;
        case DOUBLE_TAP: unregister_code(KC_C); break;
        case DOUBLE_HOLD: unregister_code(KC_C); break;
        case DOUBLE_SINGLE_TAP: unregister_code(KC_C); break;
        case TRIPLE_TAP: unregister_code(KC_C); break;
        case TRIPLE_HOLD: unregister_code(KC_C); break;
        case TRIPLE_SINGLE_TAP: unregister_code(KC_C);
    }
    ctap_state.state = 0;
};

void e_finished (qk_tap_dance_state_t *state, void *user_data) {
    etap_state.state = cur_dance(state);
    switch (etap_state.state) {
        case SINGLE_TAP: register_code(KC_E); break;
        case SINGLE_HOLD: register_code(KC_ESC); break;
        case DOUBLE_TAP: register_code(KC_E); unregister_code(KC_E); register_code(KC_E); break;
        case DOUBLE_HOLD: register_code(KC_E); break;
        case DOUBLE_SINGLE_TAP: register_code(KC_E); unregister_code(KC_E); register_code(KC_E); break;
        //Last case is for fast typing. Assuming your key is `f`:
        //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TRIPLE_TAP: register_code(KC_E); unregister_code(KC_E); register_code(KC_E); unregister_code(KC_E); register_code(KC_E); break;
        case TRIPLE_HOLD: register_code(KC_E); break;
        case TRIPLE_SINGLE_TAP: register_code(KC_E); unregister_code(KC_E); register_code(KC_E); unregister_code(KC_E); register_code(KC_E);
    }
};
void e_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (etap_state.state) {
        case SINGLE_TAP: unregister_code(KC_E); break;
        case SINGLE_HOLD: unregister_code(KC_ESC); break;
        case DOUBLE_TAP: unregister_code(KC_E); break;
        case DOUBLE_HOLD: unregister_code(KC_E); break;
        case DOUBLE_SINGLE_TAP: unregister_code(KC_E); break;
        case TRIPLE_TAP: unregister_code(KC_E); break;
        case TRIPLE_HOLD: unregister_code(KC_E); break;
        case TRIPLE_SINGLE_TAP: unregister_code(KC_E);
    }
    etap_state.state = 0;
};

void g_finished (qk_tap_dance_state_t *state, void *user_data) {
    gtap_state.state = cur_dance(state);
    switch (gtap_state.state) {
        case SINGLE_TAP: register_code(KC_G); break;
        case SINGLE_HOLD: register_code(KC_LSFT); register_code(KC_9); break;
        case DOUBLE_TAP: register_code(KC_G); unregister_code(KC_G); register_code(KC_G); break;
        case DOUBLE_HOLD: register_code(KC_G); break;
        case DOUBLE_SINGLE_TAP: register_code(KC_G); unregister_code(KC_G); register_code(KC_G); break;
        //Last case is for fast typing. Assuming your key is `f`:
        //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TRIPLE_TAP: register_code(KC_G); unregister_code(KC_G); register_code(KC_G); unregister_code(KC_G); register_code(KC_G); break;
        case TRIPLE_HOLD: register_code(KC_G); break;
        case TRIPLE_SINGLE_TAP: register_code(KC_G); unregister_code(KC_G); register_code(KC_G); unregister_code(KC_G); register_code(KC_G);
    }
};
void g_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (gtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_G); break;
        case SINGLE_HOLD: unregister_code(KC_LSFT);unregister_code(KC_9); break;
        case DOUBLE_TAP: unregister_code(KC_G); break;
        case DOUBLE_HOLD: unregister_code(KC_G); break;
        case DOUBLE_SINGLE_TAP: unregister_code(KC_G); break;
        case TRIPLE_TAP: unregister_code(KC_G); break;
        case TRIPLE_HOLD: unregister_code(KC_G); break;
        case TRIPLE_SINGLE_TAP: unregister_code(KC_G);
    }
    gtap_state.state = 0;
};

void h_finished (qk_tap_dance_state_t *state, void *user_data) {
    htap_state.state = cur_dance(state);
    switch (htap_state.state) {
        case SINGLE_TAP: register_code(KC_H); break;
        case SINGLE_HOLD: register_code(KC_LSFT); register_code(KC_0); break;
        case DOUBLE_TAP: register_code(KC_H); unregister_code(KC_H); register_code(KC_H); break;
        case DOUBLE_HOLD: register_code(KC_H); break;
        case DOUBLE_SINGLE_TAP: register_code(KC_H); unregister_code(KC_H); register_code(KC_H); break;
        //Last case is for fast typing. Assuming your key is `f`:
        //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TRIPLE_TAP: register_code(KC_H); unregister_code(KC_H); register_code(KC_H); unregister_code(KC_H); register_code(KC_H); break;
        case TRIPLE_HOLD: register_code(KC_H); break;
        case TRIPLE_SINGLE_TAP: register_code(KC_H); unregister_code(KC_H); register_code(KC_H); unregister_code(KC_H); register_code(KC_H);
    }
};
void h_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (htap_state.state) {
        case SINGLE_TAP: unregister_code(KC_H); break;
        case SINGLE_HOLD: unregister_code(KC_LSFT);unregister_code(KC_0); break;
        case DOUBLE_TAP: unregister_code(KC_H); break;
        case DOUBLE_HOLD: unregister_code(KC_H); break;
        case DOUBLE_SINGLE_TAP: unregister_code(KC_H); break;
        case TRIPLE_TAP: unregister_code(KC_H); break;
        case TRIPLE_HOLD: unregister_code(KC_H); break;
        case TRIPLE_SINGLE_TAP: unregister_code(KC_H);
    }
    htap_state.state = 0;
};

void i_finished (qk_tap_dance_state_t *state, void *user_data) {
    itap_state.state = cur_dance(state);
    switch (itap_state.state) {
        case SINGLE_TAP: register_code(KC_I); break;
        case SINGLE_HOLD: register_code(KC_ESC); break;
        case DOUBLE_TAP: register_code(KC_I); unregister_code(KC_I); register_code(KC_I); break;
        case DOUBLE_HOLD: register_code(KC_I); break;
        case DOUBLE_SINGLE_TAP: register_code(KC_I); unregister_code(KC_I); register_code(KC_I); break;
        //Last case is for fast typing. Assuming your key is `f`:
        //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TRIPLE_TAP: register_code(KC_I); unregister_code(KC_I); register_code(KC_I); unregister_code(KC_I); register_code(KC_I); break;
        case TRIPLE_HOLD: register_code(KC_I); break;
        case TRIPLE_SINGLE_TAP: register_code(KC_I); unregister_code(KC_I); register_code(KC_I); unregister_code(KC_I); register_code(KC_I);
    }
};
void i_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (itap_state.state) {
        case SINGLE_TAP: unregister_code(KC_I); break;
        case SINGLE_HOLD: unregister_code(KC_ESC); break;
        case DOUBLE_TAP: unregister_code(KC_I); break;
        case DOUBLE_HOLD: unregister_code(KC_I); break;
        case DOUBLE_SINGLE_TAP: unregister_code(KC_I); break;
        case TRIPLE_TAP: unregister_code(KC_I); break;
        case TRIPLE_HOLD: unregister_code(KC_I); break;
        case TRIPLE_SINGLE_TAP: unregister_code(KC_I);
    }
    itap_state.state = 0;
};

void n_finished (qk_tap_dance_state_t *state, void *user_data) {
    ntap_state.state = cur_dance(state);
    switch (ntap_state.state) {
        case SINGLE_TAP: register_code(KC_N); break;
        case SINGLE_HOLD: register_code(KC_LSFT); register_code(KC_RBRC); break;
        case DOUBLE_TAP: register_code(KC_N); unregister_code(KC_N); register_code(KC_N); break;
        case DOUBLE_HOLD: register_code(KC_N); break;
        case DOUBLE_SINGLE_TAP: register_code(KC_N); unregister_code(KC_N); register_code(KC_N); break;
        //Last case is for fast typing. Assuming your key is `f`:
        //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TRIPLE_TAP: register_code(KC_N); unregister_code(KC_N); register_code(KC_N); unregister_code(KC_N); register_code(KC_N); break;
        case TRIPLE_HOLD: register_code(KC_N); break;
        case TRIPLE_SINGLE_TAP: register_code(KC_N); unregister_code(KC_N); register_code(KC_N); unregister_code(KC_N); register_code(KC_N);
    }
};
void n_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (ntap_state.state) {
        case SINGLE_TAP: unregister_code(KC_N); break;
        case SINGLE_HOLD: unregister_code(KC_LSFT);unregister_code(KC_RBRC); break;
        case DOUBLE_TAP: unregister_code(KC_N); break;
        case DOUBLE_HOLD: unregister_code(KC_N); break;
        case DOUBLE_SINGLE_TAP: unregister_code(KC_N); break;
        case TRIPLE_TAP: unregister_code(KC_N); break;
        case TRIPLE_HOLD: unregister_code(KC_N); break;
        case TRIPLE_SINGLE_TAP: unregister_code(KC_N);
    }
    ntap_state.state = 0;
};

void r_finished (qk_tap_dance_state_t *state, void *user_data) {
    rtap_state.state = cur_dance(state);
    switch (rtap_state.state) {
        case SINGLE_TAP: register_code(KC_R); break;
        case SINGLE_HOLD: register_code(KC_LCTRL); register_code(KC_R); break;
        case DOUBLE_TAP: register_code(KC_R); unregister_code(KC_R); register_code(KC_R); break;
        case DOUBLE_HOLD: register_code(KC_R); break;
        case DOUBLE_SINGLE_TAP: register_code(KC_R); unregister_code(KC_R); register_code(KC_R); break;
        //Last case is for fast typing. Assuming your key is `f`:
        //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TRIPLE_TAP: register_code(KC_R); unregister_code(KC_R); register_code(KC_R); unregister_code(KC_R); register_code(KC_R); break;
        case TRIPLE_HOLD: register_code(KC_R); break;
        case TRIPLE_SINGLE_TAP: register_code(KC_R); unregister_code(KC_R); register_code(KC_R); unregister_code(KC_R); register_code(KC_R);
    }
};
void r_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (rtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_R); break;
        case SINGLE_HOLD: unregister_code(KC_LCTRL);unregister_code(KC_R); break;
        case DOUBLE_TAP: unregister_code(KC_R); break;
        case DOUBLE_HOLD: unregister_code(KC_R); break;
        case DOUBLE_SINGLE_TAP: unregister_code(KC_R); break;
        case TRIPLE_TAP: unregister_code(KC_R); break;
        case TRIPLE_HOLD: unregister_code(KC_R); break;
        case TRIPLE_SINGLE_TAP: unregister_code(KC_R);
    }
    rtap_state.state = 0;
};

void t_finished (qk_tap_dance_state_t *state, void *user_data) {
    ttap_state.state = cur_dance(state);
    switch (ttap_state.state) {
        case SINGLE_TAP: register_code(KC_T); break;
        case SINGLE_HOLD: register_code(KC_LBRC); break;
        case DOUBLE_TAP: register_code(KC_T); unregister_code(KC_T); register_code(KC_T); break;
        case DOUBLE_HOLD: register_code(KC_T); break;
        case DOUBLE_SINGLE_TAP: register_code(KC_T); unregister_code(KC_T); register_code(KC_T); break;
        //Last case is for fast typing. Assuming your key is `f`:
        //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TRIPLE_TAP: register_code(KC_T); unregister_code(KC_T); register_code(KC_T); unregister_code(KC_T); register_code(KC_T); break;
        case TRIPLE_HOLD: register_code(KC_T); break;
        case TRIPLE_SINGLE_TAP: register_code(KC_T); unregister_code(KC_T); register_code(KC_T); unregister_code(KC_T); register_code(KC_T);
    }
};
void t_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (ttap_state.state) {
        case SINGLE_TAP: unregister_code(KC_T); break;
        case SINGLE_HOLD: unregister_code(KC_LBRC); break;
        case DOUBLE_TAP: unregister_code(KC_T); break;
        case DOUBLE_HOLD: unregister_code(KC_T); break;
        case DOUBLE_SINGLE_TAP: unregister_code(KC_T); break;
        case TRIPLE_TAP: unregister_code(KC_T); break;
        case TRIPLE_HOLD: unregister_code(KC_T); break;
        case TRIPLE_SINGLE_TAP: unregister_code(KC_T);
    }
    ttap_state.state = 0;
};

void v_finished (qk_tap_dance_state_t *state, void *user_data) {
    vtap_state.state = cur_dance(state);
    switch (vtap_state.state) {
        case SINGLE_TAP: register_code(KC_V); break;
        case SINGLE_HOLD: register_code(KC_LCTRL); register_code(KC_V); break;
        case DOUBLE_TAP: register_code(KC_V); unregister_code(KC_V); register_code(KC_V); break;
        case DOUBLE_HOLD: register_code(KC_V); break;
        case DOUBLE_SINGLE_TAP: register_code(KC_V); unregister_code(KC_V); register_code(KC_V); break;
        //Last case is for fast typing. Assuming your key is `f`:
        //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TRIPLE_TAP: register_code(KC_V); unregister_code(KC_V); register_code(KC_V); unregister_code(KC_V); register_code(KC_V); break;
        case TRIPLE_HOLD: register_code(KC_V); break;
        case TRIPLE_SINGLE_TAP: register_code(KC_V); unregister_code(KC_V); register_code(KC_V); unregister_code(KC_V); register_code(KC_V);
    }
};
void v_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (vtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_V); break;
        case SINGLE_HOLD: unregister_code(KC_LCTRL); unregister_code(KC_V); break;
        case DOUBLE_TAP: unregister_code(KC_V); break;
        case DOUBLE_HOLD: unregister_code(KC_V); break;
        case DOUBLE_SINGLE_TAP: unregister_code(KC_V); break;
        case TRIPLE_TAP: unregister_code(KC_V); break;
        case TRIPLE_HOLD: unregister_code(KC_V); break;
        case TRIPLE_SINGLE_TAP: unregister_code(KC_V);
    }
    vtap_state.state = 0;
};

void x_finished (qk_tap_dance_state_t *state, void *user_data) {
    xtap_state.state = cur_dance(state);
    switch (xtap_state.state) {
        case SINGLE_TAP: register_code(KC_X); break;
        case SINGLE_HOLD: register_code(KC_LCTRL); register_code(KC_X); break;
        case DOUBLE_TAP: register_code(KC_X); unregister_code(KC_X); register_code(KC_X); break;
        case DOUBLE_HOLD: register_code(KC_X); break;
        case DOUBLE_SINGLE_TAP: register_code(KC_X); unregister_code(KC_X); register_code(KC_X); break;
        //Last case is for fast typing. Assuming your key is `f`:
        //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TRIPLE_TAP: register_code(KC_X); unregister_code(KC_X); register_code(KC_X); unregister_code(KC_X); register_code(KC_X); break;
        case TRIPLE_HOLD: register_code(KC_X); break;
        case TRIPLE_SINGLE_TAP: register_code(KC_X); unregister_code(KC_X); register_code(KC_X); unregister_code(KC_X); register_code(KC_X);
    }
};
void x_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (xtap_state.state) {
        case SINGLE_TAP: unregister_code(KC_X); break;
        case SINGLE_HOLD: unregister_code(KC_LCTRL); unregister_code(KC_X); break;
        case DOUBLE_TAP: unregister_code(KC_X); break;
        case DOUBLE_HOLD: unregister_code(KC_X); break;
        case DOUBLE_SINGLE_TAP: unregister_code(KC_X); break;
        case TRIPLE_TAP: unregister_code(KC_X); break;
        case TRIPLE_HOLD: unregister_code(KC_X); break;
        case TRIPLE_SINGLE_TAP: unregister_code(KC_X);
    }
    xtap_state.state = 0;
};

void y_finished (qk_tap_dance_state_t *state, void *user_data) {
    ytap_state.state = cur_dance(state);
    switch (ytap_state.state) {
        case SINGLE_TAP: register_code(KC_Y); break;
        case SINGLE_HOLD: register_code(KC_RBRC); break;
        case DOUBLE_TAP: register_code(KC_Y); unregister_code(KC_Y); register_code(KC_Y); break;
        case DOUBLE_HOLD: register_code(KC_Y); break;
        case DOUBLE_SINGLE_TAP: register_code(KC_Y); unregister_code(KC_Y); register_code(KC_Y); break;
        //Last case is for fast typing. Assuming your key is `f`:
        //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TRIPLE_TAP: register_code(KC_Y); unregister_code(KC_Y); register_code(KC_Y); unregister_code(KC_Y); register_code(KC_Y); break;
        case TRIPLE_HOLD: register_code(KC_Y); break;
        case TRIPLE_SINGLE_TAP: register_code(KC_Y); unregister_code(KC_Y); register_code(KC_Y); unregister_code(KC_Y); register_code(KC_Y);
    }
};
void y_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (ytap_state.state) {
        case SINGLE_TAP: unregister_code(KC_Y); break;
        case SINGLE_HOLD: unregister_code(KC_RBRC); break;
        case DOUBLE_TAP: unregister_code(KC_Y); break;
        case DOUBLE_HOLD: unregister_code(KC_Y); break;
        case DOUBLE_SINGLE_TAP: unregister_code(KC_Y); break;
        case TRIPLE_TAP: unregister_code(KC_Y); break;
        case TRIPLE_HOLD: unregister_code(KC_Y); break;
        case TRIPLE_SINGLE_TAP: unregister_code(KC_Y);
    }
    ytap_state.state = 0;
};

void z_finished (qk_tap_dance_state_t *state, void *user_data) {
    ztap_state.state = cur_dance(state);
    switch (ztap_state.state) {
        case SINGLE_TAP: register_code(KC_Z); break;
        case SINGLE_HOLD: register_code(KC_LCTRL); register_code(KC_Z); break;
        case DOUBLE_TAP: register_code(KC_Z); unregister_code(KC_Z); register_code(KC_Z); break;
        case DOUBLE_HOLD: register_code(KC_Z); break;
        case DOUBLE_SINGLE_TAP: register_code(KC_Z); unregister_code(KC_Z); register_code(KC_Z); break;
        //Last case is for fast typing. Assuming your key is `f`:
        //For example, when typing the word `buffer`, and you want to make sure that you send `ff` and not `Esc`.
        //In order to type `ff` when typing fast, the next character will have to be hit within the `TAPPING_TERM`, which by default is 200ms.
        case TRIPLE_TAP: register_code(KC_Z); unregister_code(KC_Z); register_code(KC_Z); unregister_code(KC_Z); register_code(KC_Z); break;
        case TRIPLE_HOLD: register_code(KC_Z); break;
        case TRIPLE_SINGLE_TAP: register_code(KC_Z); unregister_code(KC_Z); register_code(KC_Z); unregister_code(KC_Z); register_code(KC_Z);
    }
};
void z_reset (qk_tap_dance_state_t *state, void *user_data) {
    switch (ztap_state.state) {
        case SINGLE_TAP: unregister_code(KC_Z); break;
        case SINGLE_HOLD: unregister_code(KC_LCTRL); unregister_code(KC_Z); break;
        case DOUBLE_TAP: unregister_code(KC_Z); break;
        case DOUBLE_HOLD: unregister_code(KC_Z); break;
        case DOUBLE_SINGLE_TAP: unregister_code(KC_Z); break;
        case TRIPLE_TAP: unregister_code(KC_Z); break;
        case TRIPLE_HOLD: unregister_code(KC_Z); break;
        case TRIPLE_SINGLE_TAP: unregister_code(KC_Z);
    }
    ztap_state.state = 0;
};

qk_tap_dance_action_t tap_dance_actions[] = {
    [TD_TRIPLE_BRACE_START] = ACTION_TAP_DANCE_FN(triple_brace_start),
    [TD_TRIPLE_BRACE_END] = ACTION_TAP_DANCE_FN(triple_brace_end),
    [TD_B] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, b_finished, b_reset),
    [TD_C] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, c_finished, c_reset),
    [TD_E] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, e_finished, e_reset),
    [TD_G] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, g_finished, g_reset),
    [TD_H] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, h_finished, h_reset),
    [TD_I] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, i_finished, i_reset),
    [TD_N] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, n_finished, n_reset),
    [TD_R] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, r_finished, r_reset),
    [TD_T] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, t_finished, t_reset),
    [TD_V] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, v_finished, v_reset),
    [TD_X] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, x_finished, x_reset),
    [TD_Y] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, y_finished, y_reset),
    [TD_Z] = ACTION_TAP_DANCE_FN_ADVANCED(NULL, z_finished, z_reset)
};
