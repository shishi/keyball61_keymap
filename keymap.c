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

// double tap
enum {
  TD_CTRL_Q = 0,
  TD_CTRL_W = 1,
  TD_CTRL_E = 2,
  TD_CTRL_R = 3,
  TD_CTRL_T = 4,
  TD_CTRL_G = 5,
  TD_CTRL_Z = 6,
  TD_CTRL_X = 7,
  TD_CTRL_C = 8,
  TD_CTRL_V = 9,
  TD_CTRL_B = 10,
  TD_TRIPLE_T = 11,
  TD_TRIPLE_BRACE_START = 12,
  TD_TRIPLE_BRACE_END = 13
};

// triple tap
void triple_t(qk_tap_dance_state_t *state, void *user_data) {
    if(state->count == 1){
        register_code(KC_T);
        unregister_code(KC_T);
    }else if(state->count == 2){
        register_code(KC_T);
        unregister_code(KC_T);
    }else if(state->count == 3){
        register_code(KC_LCTL);
        register_code(KC_T);
        unregister_code(KC_T);
        unregister_code(KC_LCTL);
    }
    reset_tap_dance (state);
}

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

qk_tap_dance_action_t tap_dance_actions[] = {
  [TD_CTRL_Q]  = ACTION_TAP_DANCE_DOUBLE(KC_Q, C(KC_Q)),
  [TD_CTRL_W]  = ACTION_TAP_DANCE_DOUBLE(KC_W, C(KC_W)),
  [TD_CTRL_E]  = ACTION_TAP_DANCE_DOUBLE(KC_E, C(KC_E)),
  [TD_CTRL_R]  = ACTION_TAP_DANCE_DOUBLE(KC_R, C(KC_R)),
  [TD_CTRL_T]  = ACTION_TAP_DANCE_DOUBLE(KC_T, C(KC_T)),
  [TD_CTRL_G]  = ACTION_TAP_DANCE_DOUBLE(KC_G, C(KC_G)),
  [TD_CTRL_Z]  = ACTION_TAP_DANCE_DOUBLE(KC_Z, C(KC_Z)),
  [TD_CTRL_X]  = ACTION_TAP_DANCE_DOUBLE(KC_X, C(KC_X)),
  [TD_CTRL_C]  = ACTION_TAP_DANCE_DOUBLE(KC_C, C(KC_C)),
  [TD_CTRL_V]  = ACTION_TAP_DANCE_DOUBLE(KC_V, C(KC_V)),
  [TD_CTRL_B]  = ACTION_TAP_DANCE_DOUBLE(KC_B, C(KC_B)),
  [TD_TRIPLE_T] = ACTION_TAP_DANCE_FN(triple_t),
  [TD_TRIPLE_BRACE_START] = ACTION_TAP_DANCE_FN(triple_brace_start),
  [TD_TRIPLE_BRACE_END] = ACTION_TAP_DANCE_FN(triple_brace_end)
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_universal(
    TO(2)    , KC_1          , KC_2          , KC_3          , KC_4          , KC_5            ,                                                               KC_6          , KC_7         , KC_8         , KC_9         , KC_0            , TO(3)         ,
    KC_JYEN  , TD(TD_CTRL_Q) , TD(TD_CTRL_W) , TD(TD_CTRL_E) , TD(TD_CTRL_R) , TD(TD_TRIPLE_T) ,                                                               KC_Y          , KC_U         , KC_I         , KC_O         , KC_P            , KC_GRV        ,
    KC_MINUS , LGUI_T(KC_A)  , LALT_T(KC_S)  , LSFT_T(KC_D)  , LCTL_T(KC_F)  , TD(TD_CTRL_G)   ,                                                               KC_H          , RCTL_T(KC_J) , RSFT_T(KC_K) , RALT_T(KC_L) , RGUI_T(KC_SCLN) , LT(2,KC_QUOT) ,
    KC_EQL   , TD(TD_CTRL_Z) , TD(TD_CTRL_X) , TD(TD_CTRL_C) , TD(TD_CTRL_V) , TD(TD_CTRL_B)   , TD(TD_TRIPLE_BRACE_START),          TD(TD_TRIPLE_BRACE_END) , KC_N          , KC_M         , KC_COMM      , KC_DOT       , KC_SLSH         , KC_BSLS       ,
    KC_MEH   , KC_APP        , XXXXXXX       , XXXXXXX       , LT(3,KC_ESC)  , LT(2,KC_SPC)    , LT(1,KC_TAB) ,                      LT(1,KC_ENTER)          , LT(2,KC_BSPC) , XXXXXXX      , XXXXXXX      , XXXXXXX      , KC_PSCR         , KC_MEH
  ),

  [1] = LAYOUT_universal(
    XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                XXXXXXX , KC_INS   , KC_SCRL , XXXXXXX  , XXXXXXX , XXXXXXX ,
    KC_LALT , KC_F1   , KC_F2   , KC_F3   , KC_F4   , XXXXXXX ,                                XXXXXXX , KC_HOME  , KC_END  , XXXXXXX  , XXXXXXX , KC_RALT ,
    KC_LCTL , KC_F5   , KC_F6   , KC_F7   , KC_F8   , XXXXXXX ,                                KC_LEFT , KC_DOWN  , KC_UP   , KC_RGHT  , XXXXXXX , KC_RCTL ,
    KC_LSFT , KC_F9   , KC_F10  , KC_F11  , KC_F12  , XXXXXXX , XXXXXXX ,            XXXXXXX , XXXXXXX , KC_PGUP  , KC_PGDN , XXXXXXX  , XXXXXXX , KC_RSFT ,
    KC_LGUI , KC_F13  , KC_F14  , KC_F15  , _______ , _______ , _______ ,            _______ , KC_DEL  , XXXXXXX  , XXXXXXX , XXXXXXX  , XXXXXXX , KC_RGUI
  ),

  [2] = LAYOUT_universal(
    TO(0)   , XXXXXXX  , KC_PEQL , KC_PSLS , KC_PAST , KC_NUM  ,                                  XXXXXXX    , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , TO(0)   ,
    KC_LALT , XXXXXXX  , KC_P7   , KC_P8   , KC_P9   , KC_PMNS ,                                  XXXXXXX    , KC_HOME , KC_END  , XXXXXXX , XXXXXXX , KC_RALT ,
    KC_LCTL , XXXXXXX  , KC_P4   , KC_P5   , KC_P6   , KC_PPLS ,                                  C(KC_W)    , KC_BTN1 , KC_BTN3 , KC_BTN2 , XXXXXXX , KC_RCTL ,
    KC_LSFT , XXXXXXX  , KC_P1   , KC_P2   , KC_P3   , KC_PENT , XXXXXXX  ,            XXXXXXX  , C(S(KC_T)) , _______ , _______ , _______ , _______ , KC_RSFT ,
    KC_LGUI , XXXXXXX  , KC_0    , KC_PDOT , KC_PCMM , _______ , _______  ,            _______  , KC_DEL     , _______ , _______ , _______ , _______ , KC_RGUI
  ),

  [3] = LAYOUT_universal(
    TO(0)   , XXXXXXX  , XXXXXXX , XXXXXXX  , XXXXXXX  , XXXXXXX  ,                              XXXXXXX , XXXXXXX    , XXXXXXX    , XXXXXXX , XXXXXXX , TO(0)   ,
    XXXXXXX , KBC_RST  , XXXXXXX , CPI_D1K  , CPI_I1K  , XXXXXXX  ,                              XXXXXXX , KC_LBRC    , KC_RBRC    , XXXXXXX , XXXXXXX , XXXXXXX ,
    XXXXXXX , KBC_SAVE , XXXXXXX , CPI_D100 , CPI_I100 , XXXXXXX  ,                              XXXXXXX , S(KC_9)    , S(KC_0)    , XXXXXXX , XXXXXXX , XXXXXXX ,
    XXXXXXX , XXXXXXX  , XXXXXXX , SCRL_DVI , SCRL_DVD , XXXXXXX  , RESET ,            EEP_RST , XXXXXXX , S(KC_LBRC) , S(KC_RBRC) , XXXXXXX , XXXXXXX , XXXXXXX ,
    RESET   , XXXXXXX  , XXXXXXX , XXXXXXX  , _______  , _______  , _______ ,          _______ , KC_DEL  , XXXXXXX    , XXXXXXX    , XXXXXXX , XXXXXXX , XXXXXXX
  ),
};
// clang-format on

layer_state_t layer_state_set_user(layer_state_t state) {
    // Auto enable scroll mode when the highest layer is 3
    keyball_set_scroll_mode(get_highest_layer(state) == 1);
    return state;
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

void oledkit_render_info_user(void) {
    keyball_oled_render_keyinfo();
    keyball_oled_render_ballinfo();
}
#endif
