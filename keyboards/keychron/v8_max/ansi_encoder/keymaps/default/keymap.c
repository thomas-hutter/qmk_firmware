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

#include QMK_KEYBOARD_H
#include "keychron_common.h"
#include "sendstring_german.h"

#ifdef ACHORDION_ENABLE
#include "features/achordion.h"
#endif  // ACHORDION_ENABLE
#ifdef LAYER_LOCK_ENABLE
#include "features/layer_lock.h"
#endif  // LAYER_LOCK_ENABLE
#ifdef SELECT_WORD_ENABLE
#include "features/select_word.h"
#endif  // SELECT_WORD_ENABLE

enum layers {
    MAC_BASE,
    WIN_BASE,
    WIN_FN1,
    NUM,
    FUN,
    NAV,
    SYMR,
    // SYML,
};

// *************************************************************************************
// MISC MACROS
// *************************************************************************************
#define OSM_LS  OSM(MOD_LSFT)
#define OSM_RS  OSM(MOD_RSFT)
#define GTAB G(KC_TAB)
#define ATAB A(KC_TAB)
#define BOLD C(S(DE_F))
#define ITAL C(S(DE_K))
#define UNDR C(S(DE_U))
#define DUPLINE A(S(KC_DOWN))
#define CTXTMNU S(KC_F10)
// Bookmarks VSCODE plugin
#define BKM_TOG C(A(DE_K))
#define BKM_LST C(A(DE_L))
#define BKM_NXT C(A(DE_N))
#define BKM_PRV C(A(DE_P))

// *************************************************************************************
// ABBREVIATIONS
// *************************************************************************************
#define LS_Z    LSFT_T(DE_Z)
#define LS_X    LSFT_T(DE_X)
#define LS_Y    LSFT_T(DE_Y)
#define LS_J    LSFT_T(DE_J)
#define LC_A    LCTL(DE_A)
#define LC_C    LCTL(DE_C)
#define LC_X    LCTL(DE_X)
#define LC_V    LCTL(DE_V)
#define LC_Z    LCTL(DE_Z)
#define LC_Y    LCTL(DE_Y)
#define LC_S    LCTL(DE_S)
#define LC_F    LCTL(DE_F)
#define LC_H    LCTL(DE_H)
#define CHASH   C(DE_HASH)
#define NDIFF   C(S(DE_N))
#define PDIFF   C(S(DE_P))
#define SWVD    C(G(KC_RGHT))

// LAYER TAP SPECIAL KEYS 
#define DE_ADIAA LT(0, DE_A)
#define DE_ODIAO LT(0, DE_O)
#define DE_UDIAU LT(0, DE_U)
#define DE_SSS   LT(0, DE_S)
#define DE_QQU   LT(0, DE_Q)
#define DE_YOU   LT(0, DE_Y)
#define DE_KKL   LT(0, DE_K)
#define DE_GGR   LT(0, DE_G)
#define DE_PPL   LT(0, DE_P)
#define DE_BBL   LT(0, DE_B)
#define DE_LL   LT(0, DE_L)
#define DE_MM   LT(0, DE_M)
#define DE_TST   LT(0, DE_T)
#define DE_IIA   LT(0, DE_I)
#define DE_XEX   LT(0, DE_X)

#define HOMEND   LT(0, KC_HOME)
#define LTEQL    LT(0, DE_CIRC)
// #define TABENT   LT(0, KC_TAB)
#define XTAB     LT(0, KC_TAB)
#define MAGIC    LT(0, DE_Z)

#define MAGICF   LT(0, DE_F)
#define MAGICN   LT(0, DE_N)
#define MAGICJ   LT(0, DE_J)
#define MAGICM   LT(0, DE_M)
#define MAGICL   LT(0, DE_L)
#define MAGICO   LT(0, DE_O)


#define UNREDO   LT(0, KC_UNDO)
#define FINDF    LT(0, KC_FIND)
#define CPYCT  LT(0, KC_COPY)
#define PSTWOF LT(0, KC_PASTE)
#define BKMKMF LT(0, KC_SCROLL_LOCK)


// NUMBER ROW FUNCTION OVERLOAD 
#define DE_0F    LT(0, DE_0)
#define DE_1F    LT(0, DE_1)
#define DE_2F    LT(0, DE_2)
#define DE_3F    LT(0, DE_3)
#define DE_4F    LT(0, DE_4)
#define DE_5F    LT(0, DE_5)
#define DE_6F    LT(0, DE_6)
#define DE_7F    LT(0, DE_7)
#define DE_8F    LT(0, DE_8)
#define DE_9F    LT(0, DE_9)
#define DE_LABKF LT(0, DE_LABK) 
#define DE_HASHF LT(0, DE_HASH)

// NUMBER_ROW_FUNCTION_KEY_OVERLOAD
#define DE_F1F    LT(0, KC_F1)
#define DE_F2F    LT(0, KC_F2)
#define DE_F3F    LT(0, KC_F3)
#define DE_F4F    LT(0, KC_F4)
#define DE_F5F    LT(0, KC_F5)
#define DE_F6F    LT(0, KC_F6)
#define DE_F8F    LT(0, KC_F8)

// HOME ROW MODS 
#define HOME_T    LT(NAV, DE_T)
#define HOME_R    LSFT_T(DE_R)
#define HOME_D    LT(SYMR, DE_D)
#define HOME_N    RCTL_T(DE_N)
#define HOME_E    RSFT_T(DE_E)
#define HOME_I    LT(FUN, DE_I)
#define HOME_S    LT(NUM, DE_S)
#define WIN_W     LCTL_T(DE_W)
#define WIN_J     LCTL_T(DE_J)
//#define SYMR_C    LT(SYMR, DE_C)
#define SYMR_C    (DE_C)
#define SYML_H    (DE_H)

static bool layer_was_on_NAV_b = false;

// *************************************************************************************
// CUSTOM KEYCODES
// *************************************************************************************
enum custom_keycodes {
  CKC_ASTR = SAFE_RANGE,
  CKC_MYWORKUSER,
  CKC_EMAIL,
  CKC_MYWORKEMAIL,
  CKC_CIRC,
  CKC_AU,
  CKC_EIN,
  CKC_ADIA,
  CKC_LLCK,
  CKC_UPDR,
  CKC_SLNE,
  CKC_HEX,
  CKC_LOCIP,
  CKC_ARROW,
  CKC_LARROW,
  CKC_GRV,
  CKC_SWBK,
  CKC_SWFD,
};

// *************************************************************************************
// COMBOS
// *************************************************************************************
#include "combos.h" // define combos from combos.def

// *************************************************************************************
// KEY OVERRIDES
// *************************************************************************************
const key_override_t delete_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_BSPC, KC_DEL);
const key_override_t quot_key_override = ko_make_basic(MOD_MASK_SHIFT, DE_QUOT, DE_DQUO);
const key_override_t astr_key_override = ko_make_basic(MOD_MASK_SHIFT, DE_ASTR, DE_SLSH);
const key_override_t unds_key_override = ko_make_basic(MOD_MASK_SHIFT, DE_UNDS, DE_MINS);
const key_override_t eql_key_override = ko_make_basic(MOD_MASK_SHIFT, DE_EQL, DE_EXLM);
const key_override_t ques_key_override = ko_make_basic(MOD_MASK_SHIFT, DE_QUES, DE_EXLM);
const key_override_t lbrc_key_override = ko_make_basic(MOD_MASK_SHIFT, DE_LBRC, DE_LCBR);
const key_override_t rbrc_key_override = ko_make_basic(MOD_MASK_SHIFT, DE_RBRC, DE_RCBR);
const key_override_t bsls_key_override = ko_make_basic(MOD_MASK_SHIFT, DE_BSLS, DE_PIPE);
const key_override_t plus_key_override = ko_make_basic(MOD_MASK_SHIFT, DE_PLUS, DE_MINS);
const key_override_t ampr_key_override = ko_make_basic(MOD_MASK_SHIFT, DE_AMPR, DE_PIPE);
const key_override_t esc_override =    ko_make_basic(MOD_MASK_SHIFT, KC_ESC, DE_CIRC);
const key_override_t slsh_override = ko_make_basic(MOD_MASK_SHIFT, DE_SLSH, DE_BSLS);
const key_override_t euro_override = ko_make_basic(MOD_MASK_SHIFT, DE_EURO, DE_DLR);

// NUMPAD OVERRIDES FOR HEX VALUES
// const key_override_t P1_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_P1, S(DE_A));
// const key_override_t P2_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_P2, S(DE_B));
// const key_override_t P3_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_P3, S(DE_C));
// const key_override_t P4_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_P4, S(DE_D));
// const key_override_t P5_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_P5, S(DE_E));
// const key_override_t P6_key_override = ko_make_basic(MOD_MASK_SHIFT, KC_P6, S(DE_F));

// This globally defines all key overrides to be used
const key_override_t **key_overrides = (const key_override_t *[]){
	&delete_key_override,
  &quot_key_override,
  &astr_key_override,
  &unds_key_override,
  &eql_key_override,
  &ques_key_override,
  &lbrc_key_override,
  &rbrc_key_override,
  &bsls_key_override,
  &plus_key_override,
  &ampr_key_override,
  &euro_override,
  // &P1_key_override,
  // &P2_key_override,
  // &P3_key_override,
  // &P4_key_override,
  // &P5_key_override,
  // &P6_key_override,
  &esc_override,
  &slsh_override,
	NULL // Null terminate the array of overrides!
};

#define CW_SEND_STRING(str) \
  cw_send_string_P(PSTR(str))
static void cw_send_string_P(const char* str) {
  uint8_t saved_mods = 0;
  // If Caps Word is on, save the mods and hold Shift.
  if (is_caps_word_on()) {
    saved_mods = get_mods();
    register_mods(MOD_BIT(KC_LSFT));
  }

  send_string_P(str);  // Send the string.

  // If Caps Word is on, restore the mods.
  if (is_caps_word_on()) {
    set_mods(saved_mods);
  }
}

// *************************************************************************************
// Tap-hold configuration (https://docs.qmk.fm/tap_hold)
// *************************************************************************************
uint16_t get_tapping_term(uint16_t keycode, keyrecord_t* record) {
  switch (keycode) {
    // case DE_SSS:
    // case DE_ADIAA:
    case OSM_LS:
    case OSM_RS:
    case HOMEND:
      return TAPPING_TERM + TAPPING_TERM_EXTRA;
    default:
      return TAPPING_TERM;
  }
}

// uint16_t get_quick_tap_term(uint16_t keycode, keyrecord_t* record) {
//   // If you quickly hold a tap-hold key after tapping it, the tap action is
//   // repeated. Key repeating is useful e.g. for Vim navigation keys, but can
//   // lead to missed triggers in fast typing. Here, returning 0 means we
//   // instead want to "force hold" and disable key repeating.
//   // switch (keycode) {
//   //   case DE_N:
//   //     return QUICK_TAP_TERM;  // Enable key repeating.
//   //   default:
//   //     return 0;  // Otherwise, force hold and disable key repeating.
//   // }
//   return 0;  // Otherwise, force hold and disable key repeating.
// }

// *************************************************************************************
// CAPS WORD
// *************************************************************************************
bool caps_word_press_user(uint16_t keycode) {
    switch (keycode) {
        // Keycodes that continue Caps Word, with shift applied.
        case DE_A ... DE_Z:
        case DE_Y:
        case DE_QQU:
        case DE_YOU:
        case DE_UDIA:
        case DE_ODIA:
        case DE_ADIA:
        case DE_MINS:
        case CKC_EIN:
            add_weak_mods(MOD_BIT(KC_LSFT));  // Apply shift to next key.
            return true;
        // Keycodes that continue Caps Word, without shifting.
        case DE_1 ... DE_0:
        case KC_BSPC:
        case KC_DEL:
        case DE_UNDS:
        #ifdef CAPS_WORD_STRONG_SNAKE_CASE
        case KC_SPC:
        #endif // CAPS_WORD_STRONG_SNAKE_CASE
            return true;
        
        default:
            return false;  // Deactivate Caps Word.
    }
}


// *************************************************************************************
// LEADER KEY
// leader uses the regular keycodes, not the HOME_X 
// *************************************************************************************

#ifdef LEADER_ENABLE
void leader_start_user(void) {
    // Do something when the leader key is pressed
}

void leader_end_user(void) {
    // A
    if (leader_sequence_one_key(DE_A)) { SEND_STRING("please find my answers below."); }
    // B
    else if (leader_sequence_one_key(DE_B)) { SEND_STRING("because ");}
    // C
    else if (leader_sequence_one_key(DE_C)) { SEND_STRING("You are a  expert. "); tap_code16(KC_LEFT); tap_code16(KC_LEFT); tap_code16(C(KC_LEFT)); tap_code16(KC_LEFT);}
    else if (leader_sequence_two_keys(DE_C, DE_C)) { SEND_STRING("Rate the following prompt on a scale of 1 to 10, be brutally honest. Then ask up to 5 clarifying questions with the highest impact on a potential solution: "); }
    else if (leader_sequence_three_keys(DE_C, DE_C, DE_C)) { SEND_STRING("Provide only factual, verified information. If unsure, respond with 'I don't know.'"); }
    //else if (leader_sequence_one_key(DE_C)) { SEND_STRING(MY_WORK_USERNAME); }
    // D
    else if (leader_sequence_one_key(DE_D)) { SEND_STRING("vielen Dank"); }
    else if (leader_sequence_two_keys(DE_D, DE_D)) { SEND_STRING("vielen Dank im Voraus"); }
    //else if (leader_sequence_two_keys(DE_D, DE_H)) { SEND_STRING("please don't hesitate to contact me if you "); }
    // E
    // F
    // else if (leader_sequence_one_key(DE_F)) { tap_code16(DE_F);tap_code16(DE_UDIA);tap_code16(DE_R); }
    // G
    else if (leader_sequence_one_key(DE_G)) { SEND_STRING("guten Morgen "); }
    else if (leader_sequence_two_keys(DE_G, DE_G)) { SEND_STRING("einen wundersch"); tap_code16(DE_ODIA); SEND_STRING("nen guten Morgen ");   }
    // I
    else if (leader_sequence_one_key(DE_I)) { SEND_STRING("192.168."); }
    else if (leader_sequence_two_keys(DE_I, DE_I)) { SEND_STRING("information"); }
    // H
    // else if (leader_sequence_one_key(DE_H)) { tap_code16(DE_H); tap_code16(DE_ADIA); SEND_STRING("tte"); }
    // K
    // else if (leader_sequence_one_key(DE_K)) { tap_code16(DE_K); tap_code16(DE_ODIA); tap_code16(DE_N); tap_code16(DE_N);}
    // L
    else if (leader_sequence_one_key(DE_L)) { SEND_STRING("please let me know if you need "); }
    // M
    else if (leader_sequence_one_key(DE_M)) { SEND_STRING("mit freundlichen Gr"); 
        tap_code16(DE_UDIA); tap_code16(DE_SS); tap_code16(DE_E); tap_code16(DE_N); tap_code16(DE_COMM); tap_code16(KC_ENTER); }
    // N (not feasible since magic n prevents usage of N)
    // O
    else if (leader_sequence_one_key(DE_O)) { tap_code16(DE_ODIA); SEND_STRING("sterreich"); }
    // else if (leader_sequence_two_keys(DE_O, DE_F)) { tap_code16(DE_ODIA); SEND_STRING("ffentlich"); }
    // P
    else if (leader_sequence_one_key(DE_P)) { SEND_STRING(MY_EMAIL); }
    else if (leader_sequence_two_keys(DE_P, DE_P)) { SEND_STRING(MY_PRIVATE_EMAIL); }
    // Q (not feasible since QU)
    // else if (leader_sequence_one_key(DE_Q)) { SEND_STRING("question"); }
    // R
    else if (leader_sequence_one_key(DE_R)) { SEND_STRING("requirement"); }
    else if (leader_sequence_two_keys(DE_R, DE_S)) { SEND_STRING("responsible"); }
    else if (leader_sequence_two_keys(DE_R, DE_R)) { SEND_STRING("(0x|0X)?[a-fA-F0-9]+"); }
    // S
    else if (leader_sequence_one_key(DE_S)) { SEND_STRING("Sehr geehrter Herr "); }
    else if (leader_sequence_two_keys(DE_S, DE_S)) { SEND_STRING("Sehr geehrte Damen und Herren,"); tap_code(KC_ENT); tap_code(KC_ENT); }
    else if (leader_sequence_two_keys(DE_S, DE_D)) { SEND_STRING("Sehr geehrte Frau "); }
    // T
    else if (leader_sequence_one_key(DE_T)) { SEND_STRING("thank you"); }
    else if (leader_sequence_two_keys(DE_T, DE_D)) { SEND_STRING("Teilnehmer: Thomas Hutter, "); }
    else if (leader_sequence_two_keys(DE_T, DE_T)) { SEND_STRING("Participants: Thomas Hutter, "); }
    else if (leader_sequence_two_keys(DE_T, DE_R)) { SEND_STRING("thank you for your quick reply."); }
    // U
    else if (leader_sequence_one_key(DE_U)) { tap_code16(DE_UDIA);tap_code16(DE_B);tap_code16(DE_E);tap_code16(DE_R); }
    // V
    // else if (leader_sequence_one_key(DE_V)) { SEND_STRING("verantwortlich"); }     
    // W
    else if (leader_sequence_one_key(DE_W)) { SEND_STRING(MY_WORK_USERNAME); }
    else if (leader_sequence_two_keys(DE_W, DE_W)) { SEND_STRING(MY_WORK_EMAIL); }     

    //else if (leader_sequence_one_key(DE_W)) { tap_code16(DE_W);tap_code16(DE_UDIA);tap_code16(DE_R);tap_code16(DE_D);tap_code16(DE_E); }
    else if (leader_sequence_two_keys(DE_W, DE_R)) { SEND_STRING("I am writing to you regarding "); }     
    // else if (leader_sequence_two_keys(DE_W, DE_S)) { SEND_STRING("wie schauts aus"); }     
    // X
    else if (leader_sequence_one_key(DE_X)) { SEND_STRING("example"); }
}
#endif // LEADER_ENABLE


// *************************************************************************************
// Achordion (https://getreuer.info/posts/keyboards/achordion)
// *************************************************************************************
#ifdef ACHORDION_ENABLE
uint16_t achordion_timeout(uint16_t tap_hold_keycode) {

  switch (tap_hold_keycode) {
        case DE_UDIAU:
        case DE_ADIAA:
        // case MAGICM:
        // case MAGICL:
        case MAGICO:
        case DE_ADIA:
        case DE_ODIA:
        case DE_UDIA:
        case DE_SSS:
        case DE_XEX:
        case HOMEND:
        case DE_1F:
        case DE_2F:
        case DE_3F:
        case DE_4F:
        case DE_5F:
        case DE_6F:
        case DE_7F:
        case DE_8F:
        case DE_9F:
        case DE_0F:
        // case DE_LABKF:
        case DE_HASHF:
        case DE_QQU:
        case DE_YOU:
        case LTEQL:
        // case TABENT:
        case XTAB:
        case MAGICF:
        // case HOME_T:
        // case HOME_I:
        case FINDF:
        case CPYCT:
        case PSTWOF:
        case UNREDO:
        case BKMKMF:
        case OSM_LS:
        case OSM_RS:
        // case SYMR_C:
        // case SYML_H:
          return 0; 
        default:
          return ACHORDION_TIMEOUT;  
  }
}

bool achordion_eager_mod(uint8_t mod) {
  switch (mod) {
    case MOD_LSFT:
    case MOD_RSFT:
    case MOD_LCTL:
    case MOD_RCTL:
      return true;  // Eagerly apply Shift and Ctrl mods.

    default:
      return false;
  }
}

// Returns true if `pos` on the left hand of the keyboard, false if right.
// checked against matrix, leftmost keys of right half are col 7
static bool my_on_left_hand(keypos_t pos) {
  return pos.col < 7;
}

bool achordion_chord(uint16_t tap_hold_keycode,
                     keyrecord_t* tap_hold_record,
                     uint16_t other_keycode,
                     keyrecord_t* other_record) {
  return my_on_left_hand(tap_hold_record->event.key) !=
         my_on_left_hand(other_record->event.key);
}

#endif  // ACHORDION_ENABLE

// KC_BSPC LS_X KC_PGUP KC_PGDN
// clang-format off   
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [MAC_BASE] = LAYOUT_ansi_69(
        KC_ESC,  DE_1F,    DE_2F,    DE_3F,   DE_4F,   DE_5F,   DE_6F,              DE_7F,    DE_8F,    DE_9F,   DE_0F,    DE_SS,    KC_EQL,             KC_BSPC,             KC_ENT,
        KC_TAB,  DE_Q,     DE_W,     DE_E,    DE_R,    DE_T,                        DE_Z,     DE_U,     DE_I,    DE_O,     DE_P,     DE_UDIA,  KC_RBRC,  KC_BSLS,             HOMEND,
        KC_CAPS, DE_A,     DE_S,     DE_D,    DE_F,    DE_G,                        DE_H,     DE_J,     DE_K,    DE_L,     DE_ODIA,  DE_ADIA,            KC_ENT,              KC_DEL,
        KC_LSFT,           DE_Y,     DE_X,    DE_C,    DE_V,    DE_B,          DE_B,DE_N,     DE_M,     DE_COMM,  DE_DOT,  DE_MINS,  KC_RSFT,                     KC_UP,
        KC_LCTL, KC_LOPTN,           KC_LCMMD,         KC_SPC,  MO(WIN_FN1),        KC_ENT,             KC_SPC,            KC_RCMMD,                     KC_LEFT,  KC_DOWN,   KC_RGHT),
       
    [WIN_BASE] = LAYOUT_ansi_69(       
        KC_ESC,  UNREDO,   LC_S,     CPYCT,   PSTWOF,  FINDF,   KC_ENT,             DE_F1F,   DE_F2F,   DE_F3F,  DE_F4F,   DE_F5F,   DE_F6F,             KC_BSPC,             KC_ENT,
        KC_TAB,  DE_Z,     DE_M,     DE_L,    DE_G,    DE_P,                        TG(FUN),  DE_QQU,   DE_F,    MAGICO,   DE_UDIAU, CKC_ASTR, DE_PLUS,  DE_QUES,             HOMEND,
        KC_BSPC, DE_D,     HOME_S,   HOME_R,  HOME_T,  DE_B,                        CKC_SWBK,  DE_Y,     MAGICN,  HOME_E,   DE_I,   DE_ADIAA,           KC_ENT,              KC_DEL,
        OSM_LS,            DE_K,     DE_V,    SYMR_C,  WIN_W,   DE_X,       BKMKMF, QK_LEAD,  WIN_J,    SYML_H,  DE_COMM,  DE_DOT,   OSM_RS,                      KC_UP,
        KC_LCTL, KC_LWIN,            KC_LALT,          OSL(SYMR),DE_UNDS,           KC_TAB,             KC_SPC,            KC_LALT,                       KC_LEFT,  KC_DOWN,   KC_RGHT),
       
    [NUM] = LAYOUT_ansi_69(       
        _______,  _______,  _______,  _______, _______, _______, _______,           S(DE_A),  S(DE_B),  S(DE_C), S(DE_D),  S(DE_E),  S(DE_F),            KC_BSPC,             KC_ENT,
        _______,  _______,  _______,  _______, _______, _______,                    DE_DLR,   CKC_CIRC, DE_7,     DE_8,    DE_9,     KC_PMNS,   DE_PERC,  CKC_HEX,              _______,
        _______,  KC_LWIN,  _______,  _______, KC_LWIN, _______,                    DE_EURO,  KC_PAST,  DE_1,     DE_2,    DE_3,     DE_0,                     _______,             _______,
        KC_LSFT,            _______,  _______, _______, _______,_______,   KC_CALC, DE_DOT,   KC_PSLS,  DE_4,     DE_5,    DE_6,     KC_PPLS,                        _______,
        _______, _______,            _______,          CKC_LLCK, CKC_LLCK,                DE_DOT,            DE_COMM,           KC_SPC,                       _______,  _______,   _______),    

    [FUN] = LAYOUT_ansi_69(       
        _______, KC_F1,    KC_F2,    KC_F3,   KC_F4,   KC_F5, KC_F6,                KC_F7,    KC_F8,    KC_F9,   KC_F10,   KC_F11,    KC_F12,            _______,             RGB_TOG,
        _______, KC_F12,   KC_F9,    KC_F8,   KC_F7,   XXXXXXX,                     TG(FUN),  _______,  _______, _______,  _______,   _______,  _______,  _______,             _______,
        _______, KC_F10,   KC_F3,    KC_F2,   KC_F1,   XXXXXXX,                     _______,  _______,  _______, KC_RSFT,  _______,   _______,            _______,             _______,
        KC_F11,            KC_F6,    KC_F5,   KC_F4,   XXXXXXX, _______,    _______,_______,  _______,  _______, _______,  _______,   _______,                     _______,
        _______, _______,            _______,          CKC_LLCK, CKC_LLCK,                 _______,           _______,           _______,                       _______, _______,   _______),
    
    [NAV] = LAYOUT_ansi_69(        
        _______, _______,  _______,  _______, _______, _______, _______,            DE_F1F,   DE_F2F,   DE_F3F,   DE_F4F,  DE_F5F,  DE_F6F,               KC_BSPC,             KC_ENT,
        _______, _______,  DUPLINE,  BOLD,    ITAL,    UNDR,                        XXXXXXX, C(KC_HOME), KC_HOME, KC_UP,   KC_END,  C(KC_END),    _______,  _______,             _______,
        _______, KC_LWIN,  KC_LCTL,  KC_LSFT, KC_LCTL, PDIFF,                       XXXXXXX,  KC_BSPC,  KC_LEFT,  KC_DOWN, KC_RGHT, KC_DEL,                _______,             _______,
        KC_LSFT,           BKM_LST,  BKM_TOG, KC_ESC,  NDIFF,   _______,    _______,XXXXXXX,  CKC_SWBK, C(KC_LEFT),CKC_SLNE,C(KC_RIGHT),CKC_SWFD,                       _______,
        _______, _______,            _______,          CKC_LLCK,CKC_LLCK,              _______,           _______,           _______,                      _______,  _______,   _______),        
       
    [SYMR] = LAYOUT_ansi_69(       
       _______, DE_EXLM,  DE_DQUO,  DE_EURO, DE_DLR,  DE_PERC, DE_SECT,              BT_HST1,  CKC_CIRC, DE_RCBR, DE_RBRC, DE_DLR,  CKC_GRV,           _______,             KC_MUTE,
       _______, CKC_CIRC, DE_LABK,  DE_MINS, DE_RABK, DE_PIPE,                       BT_HST2,  DE_PIPE,  DE_LCBR, DE_LBRC, DE_HASH, DE_TILD,    DE_PERC,  DE_EXLM,             QK_BOOT,
       _______, DE_TILD,  DE_SS,    DE_PLUS, LTEQL,   DE_AMPR,                       BT_HST3,  DE_AMPR,  DE_LPRN, DE_RPRN, LTEQL,   DE_QUOT,            _______,             _______,
       _______,           XXXXXXX,  CKC_GRV,  DE_BSLS, DE_SLSH, DE_MICR,     _______,DE_MICR,  DE_BSLS,  DE_SLSH, DE_SCLN, DE_COLN, DE_DQUO,            _______,
       _______, _______,            _______,      TG(WIN_FN1), TG(WIN_FN1),          TG(WIN_FN1),            DE_MINS,           _______,                       _______, _______,   _______),
      
    // [SYML] = LAYOUT_ansi_69(       
    //      _______, DE_EXLM,  DE_DQUO,  DE_EURO, DE_DLR,  DE_PERC, DE_SECT,            _______,  _______,  _______, _______,  _______,  _______,            _______,             RGB_TOG,
    //      _______, CKC_CIRC, DE_LABK,  DE_MINS, DE_RABK, DE_PIPE,                     _______,  _______,  _______, _______,  _______,  _______,  _______,  _______,             _______,
    //      _______, DE_TILD,  DE_SS,    DE_PLUS, LTEQL,   DE_AMPR,                     _______,  _______,  _______, KC_RSFT, _______,  _______,            _______,             _______,
    //      _______,           XXXXXXX,  CKC_GRV,  DE_BSLS, DE_SLSH, DE_MICR,            _______,  _______,  _______, _______,  _______,  _______,  _______,           _______,
    //      _______, _______,            _______,      TG(WIN_FN1), TG(WIN_FN1),        _______,           _______,           _______,                       _______, _______,   _______),
           
    [WIN_FN1] = LAYOUT_ansi_69(       
      KC_ESC,  KC_BRID,  KC_BRIU,  KC_TASK, KC_FILE, RGB_VAD, RGB_VAI,            KC_MPRV,  KC_MPLY,  KC_MNXT, KC_MUTE,  KC_VOLD,  KC_VOLU,            _______,             RGB_TOG,
      _______, BT_HST1,  BT_HST2,  BT_HST3, P2P4G,   _______,                     _______,  _______,  _______, _______,  _______,  _______,  _______,  _______,             QK_BOOT,
      RGB_TOG, RGB_MOD,  RGB_VAI,  RGB_HUD, RGB_SAI, RGB_SPI,                     _______,  _______,  _______, _______,  _______,  _______,            _______,             KC_END,
      _______,           RGB_RMOD, RGB_VAD, RGB_HUI, RGB_SAD, RGB_SPD,            RGB_SPD,  NK_TOGG,  _______, _______,  _______,  _______,  _______,            _______,
      _______, _______,            _______,          TG(WIN_FN1), TG(WIN_FN1),            _______,            _______,           _______,                      _______,  _______,   _______),
       
};

// clang-format on
#if defined(ENCODER_MAP_ENABLE)
const uint16_t PROGMEM encoder_map[][NUM_ENCODERS][2] = {
    [MAC_BASE] = {ENCODER_CCW_CW(KC_PGUP, KC_PGDN)},
    [WIN_BASE] = {ENCODER_CCW_CW(KC_PGUP, KC_PGDN)},
    [WIN_FN1] = {ENCODER_CCW_CW(RGB_VAD, RGB_VAI)},
    [NUM] = {ENCODER_CCW_CW(KC_PGUP, KC_PGDN)},
    [FUN] = {ENCODER_CCW_CW(KC_PGUP, KC_PGDN)},
    [NAV] = {ENCODER_CCW_CW(KC_PGUP, KC_PGDN)},
    // [SYML] = {ENCODER_CCW_CW(KC_PGUP, KC_PGDN)},
    [SYMR] = {ENCODER_CCW_CW(KC_VOLD, KC_VOLU)},
};
#endif // ENCODER_MAP_ENABLE


// *************************************************************************************
// LED_COLORS_REFLECT_CURRENT_LAYER  
// *************************************************************************************
layer_state_t layer_state_set_user(layer_state_t state) {
    switch (get_highest_layer(state)) {
      case WIN_FN1:
          rgb_matrix_enable_noeeprom();
          rgb_matrix_sethsv_noeeprom (HSV_GREEN);          
          break;
      case NAV:
          rgb_matrix_enable_noeeprom();
          rgb_matrix_sethsv_noeeprom (HSV_BLUE);
          
          break;
      case NUM:
      case FUN:
          rgb_matrix_enable_noeeprom();
          rgb_matrix_sethsv_noeeprom (HSV_YELLOW);
          break;
      default: //  for any other layers, or the default layer
          rgb_matrix_disable_noeeprom();
          // rgb_matrix_sethsv_noeeprom (HSV_RED);
          break;
    }
  return state;
}

// *************************************************************************************
// CUSTOM LONG PRESS  
// *************************************************************************************
// Helper for implementing tap vs. long-press keys. Given a tap-hold
// key event, replaces the hold function with `long_press_keycode`.
static bool process_tap_or_long_press_key(
    keyrecord_t* record, uint16_t long_press_keycode) {
  if (record->tap.count == 0) {  // Key is being held.
    if (record->event.pressed) {
      tap_code16(long_press_keycode);
    }
    return false;  // Skip default handling.
  }
  return true;  // Continue default handling.
}


// *************************************************************************************
// COMBOS: require prior idle and term per combo
// *************************************************************************************
// static uint16_t require_prior_idle_timer = 0;

// bool combo_should_trigger(uint16_t combo_index, combo_t *combo, uint16_t keycode, keyrecord_t *record) {
//     /* Disable combos while prior idle timer is running */
//     // if(require_prior_idle_timer != 0){
//     //   return false;
//     // } else {
//     //   return true;
//     // }    
//     return true;
// }

uint16_t get_combo_term(uint16_t index, combo_t *combo) {
    // or with combo index, i.e. its name from enum.
    // due to the combos.h implementation, the resulting name is C_YourMacroName
    switch (index) {
        // non home row combos get a tighter activation time
        // case C_combo_end:
        // case C_combo_tab:
        // case C_combo_home:
        // case C_combo_esc:
        // case combo_bpar:       
          // return COMBO_TERM;
          // break;
        //case C_combo_uo:
        // case C_combo_ae:
        // case C_combo_cv:
          //case C_combo_ml:
          //case C_combo_lm: return COMBO_TERM_DIRECTIONAL;          
        // case C_combo_cn:
        // case C_combo_pn:
        // case C_combo_bn:
        //   return COMBO_TERM_DIRECTIONAL_2HANDS;
        //   break;  
        case C_combo_ein: 
        case C_combo_rarrow:
        case C_combo_larrow:
        case C_combo_at:
        case C_combo_commdot:
        case C_combo_slsh:
          return COMBO_TERM_SLOW*4; 
        default: return COMBO_TERM_SLOW;
    }    
}

// bool get_combo_must_press_in_order(uint16_t combo_index, combo_t *combo) {
//     switch (combo_index) {
//         /* List combos here that you want to only activate if their keys
//          * are pressed in the same order as they are defined in the combo's key
//          * array. */
//           //case C_combo_uo:
//         // case C_combo_ae:
//         // case C_combo_ml:
//         // case C_combo_lm:
//         // case C_combo_cv:
//         // case C_combo_cn:
//         // case C_combo_pn:
//         // case C_combo_bn:
//             //return true;
//         default:
//             return false;
//     }
// }


// *************************************************************************************
// Repeat key (https://docs.qmk.fm/features/repeat_key)
// *************************************************************************************
#ifdef REPEAT_KEY_ENABLE
// uint16_t get_alt_repeat_key_keycode_user(uint16_t keycode, uint8_t mods) {
//   if ((mods & ~MOD_MASK_SHIFT) == 0) {
//     // This is where most of the "magic" for the MAGIC key is implemented.
//     switch (keycode) {
//       case DE_G: return DE_R;
//       case DE_P: return DE_R;
//       case NUM_B: return DE_L;
//       case HOME_T: return M_TMENT;
//       case SYMR_C: return DE_K;
//       default: return DE_F;
//     }
//   }
//   return KC_TRNS;
// }

bool remember_last_key_user(uint16_t keycode, keyrecord_t* record,
                            uint8_t* remembered_mods) {
    switch (keycode) {
        case MAGICN:
        // case MAGICM:
        // case MAGICL:
        case MAGICO:
        case MAGIC:        
            return false;  // Ignore ALTREP keys.
    }
    return true;  // Other keys can be repeated.
}

// An enhanced version of SEND_STRING: if Caps Word is active, the Shift key is
// held while sending the string. Additionally, the last key is set such that if
// the Repeat Key is pressed next, it produces `repeat_keycode`. This helper is
// used for several macros below in my process_record_user() function.
#define MAGIC_STRING(str, repeat_keycode) \
  magic_send_string_P(PSTR(str), (repeat_keycode))
static void magic_send_string_P(const char* str, uint16_t repeat_keycode) {
  uint8_t saved_mods = 0;
  // If Caps Word is on, save the mods and hold Shift.
  if (is_caps_word_on()) {
    saved_mods = get_mods();
    register_mods(MOD_BIT(KC_LSFT));
  }

  send_string_P(str);  // Send the string.
  set_last_keycode(repeat_keycode);

  // If Caps Word is on, restore the mods.
  if (is_caps_word_on()) {
    set_mods(saved_mods);
  }
}

static void process_magicn(uint16_t keycode, uint8_t mods) {

    switch (keycode) {
      case DE_P:
      case DE_PPL: MAGIC_STRING("r", DE_N); break;
      //case NUM_B: 
      //case DE_B: MAGIC_STRING("r", DE_N); break;
      case SYMR_C: MAGIC_STRING("h", DE_N); break;
      case DE_Z: MAGIC_STRING("w", DE_N); break;
      case DE_V: MAGIC_STRING("er", DE_N); break;
      default: MAGIC_STRING("n", DE_N); 
    }
}

static void process_magico(uint16_t keycode, uint8_t mods) {
    uint8_t oneshot_mods = get_oneshot_mods();
    switch (keycode) {
        case DE_U:
        case DE_UDIAU:
            unregister_mods(MOD_MASK_CSAG);
            tap_code(KC_BSPC);
            if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
                MAGIC_STRING("Au", DE_U);
            } else {
                MAGIC_STRING("au", DE_U);
            }
            break;
        default:
            MAGIC_STRING("o", DE_O);
            if(oneshot_mods & MOD_MASK_SHIFT) {set_last_mods(MOD_BIT(KC_LSFT));}
            break;
    }
}


// static void process_magic(uint16_t keycode, uint8_t mods) {
//     switch (keycode) {
//       case HOME_E: MAGIC_STRING("in", DE_N); break;
//       case DE_F: tap_code16(DE_UDIA); MAGIC_STRING("r", DE_N);  break;
//       case DE_K: tap_code16(DE_ODIA); MAGIC_STRING("nn", DE_N);  break;
//       case DE_U: 
//       case DE_UDIAU:
//         // const uint8_t oneshot_mods = get_oneshot_mods();
//         // clear_oneshot_mods();  // Temporarily disable mods.
//         unregister_mods(MOD_MASK_CSAG);
//         tap_code16(KC_BSPC);
//         if ((mods) & MOD_MASK_SHIFT) { tap_code16(S(DE_UDIA));              
//         } else {tap_code(DE_UDIA);  }      
//         MAGIC_STRING("ber", DE_N); 
//         register_mods(mods);break;
//       case DE_O: 
//         // const uint8_t oneshot_mods = get_oneshot_mods();
//         // clear_oneshot_mods();  // Temporarily disable mods.
//         unregister_mods(MOD_MASK_CSAG);
//         tap_code16(KC_BSPC);
//         if ((mods) & MOD_MASK_SHIFT) { tap_code16(S(DE_ODIA));              
//         } else {tap_code(DE_ODIA);  }       
//         register_mods(mods);break;
//       case CKC_ADIA:
//       case DE_ADIA:
//       case DE_ADIAA:
//       case DE_A: MAGIC_STRING("u", HOME_I); break;
//       case DE_N: MAGIC_STRING("g", DE_N); break;
//       case HOME_S: MAGIC_STRING("ch", DE_N); break;
//       case HOME_I: MAGIC_STRING("ch", DE_N); break;
//       case SYML_H: MAGIC_STRING("n", DE_N); break;
//       case HOME_T: MAGIC_STRING("ion", DE_N); break;
//       case DE_Y: MAGIC_STRING("ou", DE_QUOT); break;
//       case DE_DOT: MAGIC_STRING("./", DE_SECT); break;
//       case DE_SECT: MAGIC_STRING("../", DE_SECT); break;
//       case DE_QUOT: tap_code16(DE_QUOT); break;
//       case CKC_ASTR:
//       case DE_ASTR: tap_code16(KC_BSPC); tap_code16(DE_DOT); tap_code16(DE_ASTR); break;
//       case DE_SLSH:
//       case DE_PERC:
//       case DE_PIPE:
//       case DE_AMPR:
//       case DE_MINS:
//       case DE_RABK:
//       case DE_EXLM:
//       case DE_QUES:
//       case CKC_CIRC:
//       case DE_TILD:
//       case DE_SCLN:
//       case DE_COLN:
//       case DE_PLUS: MAGIC_STRING("=", DE_PLUS); break;
//       case LTEQL:
//       case DE_EQL: MAGIC_STRING(" \'", DE_PLUS); break;
//       case DE_HASH:
//       case DE_HASHF: MAGIC_STRING("include \"", DE_PLUS); break;
//       case KC_SPC:
//       case KC_TAB:
//       case KC_ENT: 
//       default:
//         const uint8_t mods = get_mods();
//         // const uint8_t oneshot_mods = get_oneshot_mods();
//         // clear_oneshot_mods();  // Temporarily disable mods.
//         unregister_mods(MOD_MASK_CSAG);
//         if ((mods) & MOD_MASK_SHIFT) { tap_code16(S(DE_T));              
//         } else {tap_code(DE_T);  }
//         tap_code16(DE_H);
//         tap_code16(DE_E);
//         register_mods(mods);
//         set_last_keycode(DE_Q);
//     }
// }


// combine magic
static void process_magic(uint16_t keycode, uint8_t mods) {

    switch (keycode) {
      case HOME_E: MAGIC_STRING("in", DE_N); break;
      // case DE_F: tap_code16(DE_UDIA); MAGIC_STRING("r", DE_N);  break;
      // case DE_N: MAGIC_STRING("g", DE_N); break;
      case CKC_ADIA:
      case DE_ADIA:
      case DE_ADIAA:
      case DE_A: MAGIC_STRING("u", DE_SECT); break;
      case DE_Y: MAGIC_STRING("ou", DE_N); break;
      case DE_SECT: MAGIC_STRING("ch", DE_N); break;
      case KC_SPC:
      case KC_TAB:
      case KC_ENT: 
      default:
        set_oneshot_mods(MOD_BIT(KC_LSFT));
    }
}


// static void process_magic(uint16_t keycode, uint8_t mods) {

//     switch (keycode) {
//       case HOME_E: MAGIC_STRING("in", DE_N); break;
//       case DE_F: tap_code16(DE_UDIA); MAGIC_STRING("r ", DE_N);  break;
//       // case DE_SSS: MAGIC_STRING("t", DE_N); break;
//       // case DE_ODIAO: MAGIC_STRING("f", DE_N); break;
//       // case DE_UDIAU: MAGIC_STRING("nd ", DE_N); break;
//       // case DE_ADIAA: MAGIC_STRING("u", HOME_I); break;
//       // case DE_N: MAGIC_STRING("g", DE_N); break;
//       // case HOME_I: MAGIC_STRING("ch", DE_N); break;
//       case SYML_H: MAGIC_STRING("n", DE_N); break;
//       // case DE_N:
//       // case HOME_R:
//       // case HOME_T: MAGIC_STRING("z", DE_N); break;
//       // case DE_YOU: MAGIC_STRING("ou", DE_N); break;
//       case KC_SPC:
//       case KC_TAB:
//       case KC_ENT: 
//         const uint8_t mods = get_mods();
//         // const uint8_t oneshot_mods = get_oneshot_mods();
//         // clear_oneshot_mods();  // Temporarily disable mods.
//         unregister_mods(MOD_MASK_CSAG);
//         if ((mods) & MOD_MASK_SHIFT) { tap_code16(S(DE_T));              
//         } else {tap_code(DE_T);  }
//         tap_code16(DE_H);
//         tap_code16(DE_E);
//         register_mods(mods);
//         set_last_keycode(DE_Q);
//         break;      
//       case DE_Q: MAGIC_STRING("y", DE_SECT); break;
//       case DE_DOT: MAGIC_STRING("./", DE_SECT); break;
//       case DE_SECT: MAGIC_STRING("../", DE_SECT); break;
//       case DE_SLSH:
//       case CKC_ASTR:
//       case DE_PERC:
//       case DE_PIPE:
//       case DE_AMPR:
//       case DE_MINS:
//       case DE_RABK:
//       case DE_EXLM:
//       case DE_QUES:
//       case CKC_CIRC:
//       case DE_TILD:
//       case DE_SCLN:
//       case DE_COLN:
//       case DE_PLUS: MAGIC_STRING("=", DE_PLUS); break;
//       case LTEQL:
//       case DE_EQL: MAGIC_STRING(" \'", DE_PLUS); break;
//       case DE_HASH:
//       case DE_HASHF: MAGIC_STRING("include \"", DE_PLUS); break;
//       default: MAGIC_STRING("ch", DE_N); 
//     }
// }
#endif // REPEAT_KEY_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // On every key event, set require_prior_idle_timer to expire after IDLE_TIMEOUT_MS.
    // We use require_prior_idle_timer == 0 to indicate that the timer is inactive, so
    // the value is bitwise or'd with 1 to ensure it is nonzero.
    // require_prior_idle_timer = (record->event.time + REQUIRE_PRIOR_IDLE_TIMEOUT) | 1;
    #ifdef ACHORDION_ENABLE
      if (!process_achordion(keycode, record)) { return false; }
    #endif  // ACHORDION_ENABLE
    
    #ifdef LAYER_LOCK_ENABLE
      if (!process_layer_lock(keycode, record, CKC_LLCK)) { return false; }
    #endif  // LAYER_LOCK_ENABLE
    
    #ifdef USER_NUM_WORD_ENABLE
      if (!process_record_num_word(keycode, record)) { return false; }
    #endif // USER_NUM_WORD_ENABLE

    #ifdef SELECT_WORD_ENABLE
      if (!process_select_word(keycode, record)) { return false; }
    #endif  // SELECT_WORD_ENABLE

    if (!process_record_keychron_common(keycode, record)) { return false; }

    const uint8_t mods = get_mods();
    const uint8_t oneshot_mods = get_oneshot_mods();

    switch (keycode) {
        case DE_ADIAA:  return process_tap_or_long_press_key(record, DE_ADIA); break;
        case DE_UDIAU:  return process_tap_or_long_press_key(record, DE_UDIA); break;
        case DE_SSS:    return process_tap_or_long_press_key(record, DE_SS); break;
        // case DE_1F:     return process_tap_or_long_press_key(record, KC_F1); break;
        // case DE_2F:     return process_tap_or_long_press_key(record, KC_F2); break;
        // case DE_3F:     return process_tap_or_long_press_key(record, KC_F3); break;
        // case DE_4F:     return process_tap_or_long_press_key(record, KC_F4); break;
        // case DE_5F:     return process_tap_or_long_press_key(record, KC_F5); break;
        // case DE_6F:     return process_tap_or_long_press_key(record, KC_F6); break;
        // case DE_7F:     return process_tap_or_long_press_key(record, KC_F7); break;
        // case DE_8F:     return process_tap_or_long_press_key(record, KC_F8); break;
        // case DE_9F:     return process_tap_or_long_press_key(record, KC_F9); break;
        // case DE_0F:     return process_tap_or_long_press_key(record, KC_F10); break; 
        // case DE_LABKF:  return process_tap_or_long_press_key(record, KC_F11); break;
        // case DE_HASHF:  return process_tap_or_long_press_key(record, KC_F12); break; 
        case DE_F1F:     return process_tap_or_long_press_key(record, KC_F7); break;
        case DE_F2F:     return process_tap_or_long_press_key(record, KC_F8); break;
        case DE_F3F:     return process_tap_or_long_press_key(record, KC_F9); break;
        case DE_F4F:     return process_tap_or_long_press_key(record, KC_F10); break;
        case DE_F5F:     return process_tap_or_long_press_key(record, KC_F11); break;
        case DE_F6F:     return process_tap_or_long_press_key(record, KC_F12); break;
        case DE_F8F:     return process_tap_or_long_press_key(record, KC_F9); break;
        case HOMEND:    return process_tap_or_long_press_key(record, KC_END); break; 
        // case TABENT:    return process_tap_or_long_press_key(record, KC_ENT); break; 

        case MAGICO:
            if (record->tap.count > 0) {    // Key is being tapped.
              if (record->event.pressed) { process_magico(get_last_keycode(), get_last_mods());} 
              else {}    // Handle tap release event...
            } else {                        // Key is being held.
                if (record->event.pressed) { tap_code16(DE_ODIA);} 
                else {}// Handle hold release event...
            } 
            return false;  // Skip default handling
        case MAGICN: 
          if (record->tap.count > 0) {    // Key is being tapped.
              if (record->event.pressed) { 
                process_magicn(get_last_keycode(), get_last_mods()); 
                set_last_keycode(DE_N);
              } 
            } else {                        // Key is being held.
                if (record->event.pressed) { layer_on(FUN); } 
                else {layer_off(FUN);}
            } 
            return false;  // Skip default handling  
        case MAGIC: 
          if (record->tap.count > 0) {    // Key is being tapped.
              if (record->event.pressed) { process_magic(get_last_keycode(), get_last_mods());} 
              else {}    // Handle tap release event...
            } else {                        // Key is being held.
                if (record->event.pressed) { tap_code16(DE_Z);} 
                else {}// Handle hold release event...
            } 
            return false;  // Skip default handling           
        case DE_QQU:     
          if ((record->tap.count > 0)&&(record->event.pressed)) { CW_SEND_STRING("qu"); } // Key is being tapped.
          else { if (record->event.pressed) { tap_code16(DE_Q); } // key is being held
          } return false;  // Skip default handling
        case DE_HASHF:     
          if ((record->tap.count > 0)&&(record->event.pressed)) { tap_code16(DE_HASH); } // Key is being tapped.
          else { if (record->event.pressed) { tap_code16(CHASH); } // key is being held
          } return false;  // Skip default handling
        case XTAB:     
          if ((record->tap.count > 0)&&(record->event.pressed)) { tap_code16(ATAB); } // Key is being tapped.
          else { 
            if (record->event.pressed) { // key is being held
              tap_code16(GTAB); 
              if (layer_state_is(NAV) == false)
              {
                layer_on(NAV);
                layer_was_on_NAV_b = false;
              } else {layer_was_on_NAV_b = true;}
            } else // Handle hold release event...
            {
              tap_code16(KC_ENTER);
              if (layer_was_on_NAV_b == false)
              {
                layer_off(NAV);
              }  
            }
          } 
          return false;  // Skip default handling
        case FINDF:     
          if ((record->tap.count > 0)&&(record->event.pressed)) { tap_code16(C(DE_F)); } // Key is being tapped.
          else { if (record->event.pressed) { tap_code16(S(C(DE_F))); } // key is being held
          } return false;  // Skip default handling
        case UNREDO:     
          if ((record->tap.count > 0)&&(record->event.pressed)) { tap_code16(C(DE_Z)); } // Key is being tapped.
          else { if (record->event.pressed) { tap_code16(C(DE_Y)); } // key is being held
          } return false;  // Skip default handling          
        case CPYCT:     
          if ((record->tap.count > 0)&&(record->event.pressed)) { tap_code16(C(DE_C)); } // Key is being tapped.
          else { if (record->event.pressed) { tap_code16(C(DE_X)); } // key is being held
          } return false;  // Skip default handling
        case PSTWOF:     
          if ((record->tap.count > 0)&&(record->event.pressed)) { tap_code16(C(DE_V)); } // Key is being tapped.
          else { if (record->event.pressed) { tap_code16(S(C(DE_V))); } // key is being held
          } return false;  // Skip default handling
        case BKMKMF:     
          if ((record->tap.count > 0)&&(record->event.pressed)) { tap_code16(A(C(DE_K))); } // Key is being tapped.
          else { if (record->event.pressed) { tap_code16(A(C(DE_L))); } // key is being held
          } return false;  // Skip default handling
        // case DE_XEX:     
        //   if ((record->tap.count > 0)&&(record->event.pressed)) { CW_SEND_STRING("ex"); } // Key is being tapped.
        //   else { if (record->event.pressed) { tap_code16(DE_X); } // key is being held
        //   } return false;  // Skip default handling   
        // case DE_YOU:     
        //   if (record->tap.count > 0) { break; } // Key is being tapped.
        //   else { if (record->event.pressed) { CW_SEND_STRING("you"); } // key is being held
        //   } return false;  // Skip default handling     
        case CKC_SWBK:  // Backward word selection.
          if (record->event.pressed) {
            select_word_register('B');
          } else {
            select_word_unregister();
          }
          break;
        case CKC_SWFD:  // Forward word selection.
          if (record->event.pressed) {
            select_word_register('W');
          } else {
            select_word_unregister();
          }
          break;
        default:
          break;

    }

    if (record->event.pressed) {
      switch (keycode) {
        case CKC_LOCIP: CW_SEND_STRING("192.168."); return false;
        case CKC_ARROW: tap_code16(DE_MINS); tap_code16(DE_RABK); return false;    
        case CKC_LARROW: tap_code16(DE_LABK); tap_code16(DE_MINS);return false;    
        case CKC_CIRC: send_string("^"); break;
        case CKC_GRV:  send_string("`"); break;
        case CKC_ASTR:  
          clear_oneshot_mods();  // Temporarily disable mods.
          unregister_mods(MOD_MASK_CSAG);
          if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {tap_code16(DE_DOT); tap_code16(DE_ASTR); 
          } else if ((mods | oneshot_mods) & MOD_MASK_CTRL) {tap_code16(DE_ASTR); tap_code16(DE_DOT); 
          } else {tap_code16(DE_ASTR); }
          register_mods(mods);  // Restore mods.
          return false;         
        case LTEQL:  
          clear_oneshot_mods();  // Temporarily disable mods.
          unregister_mods(MOD_MASK_CSAG);
          if ((mods | oneshot_mods) & MOD_MASK_SHIFT) { tap_code16(DE_EXLM); tap_code16(DE_EQL); tap_code(KC_SPC); 
          } else {tap_code16(DE_EQL); }
          register_mods(mods);  // Restore mods.
          return false;       
        case CKC_MYWORKUSER: send_string(MY_WORK_USERNAME); return false;
        case CKC_EMAIL: send_string(MY_EMAIL); return false;
        case CKC_MYWORKEMAIL: send_string(MY_WORK_EMAIL); return false;        
        case CKC_UPDR: 
          clear_oneshot_mods();  // Temporarily disable mods.
          unregister_mods(MOD_MASK_CSAG);
          if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
            SEND_STRING_DELAY("../", TAP_CODE_DELAY);
          } else {            
            SEND_STRING_DELAY("cd ../", TAP_CODE_DELAY);
          }
          register_mods(mods);  // Restore mods.
          return false;
        case CKC_SLNE:   SEND_STRING_DELAY(SS_TAP(X_HOME) SS_LSFT(SS_TAP(X_END)), TAP_CODE_DELAY); return false;
        case CKC_HEX:       tap_code16(DE_0); tap_code16(DE_X); return false;
        // case KC_SPC:    
        //   if ((oneshot_mods) & MOD_MASK_SHIFT) { tap_code(DE_MINS); return false; } 
        //   #ifdef CAPS_WORD_STRONG_SNAKE_CASE   
        //   if (is_caps_word_on()) { tap_code16(DE_UNDS); return false; } // change caps word to strong snake case
        //   #endif // CAPS_WORD_STRONG_SNAKE_CASE
        //   break;
        case CKC_AU:      
          clear_oneshot_mods();  // Temporarily disable mods.
          unregister_mods(MOD_MASK_CSAG);  
          if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
              SEND_STRING("Au");
            } else { SEND_STRING("au"); }
          set_last_keycode(DE_UDIA);
          register_mods(mods);  // Restore mods. 
          layer_off(SYMR); 
          return false;
        // case CKC_ADIA:      
        //   clear_oneshot_mods();  // Temporarily disable mods.
        //   unregister_mods(MOD_MASK_CSAG);  
        //   if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
        //       tap_code16(S(DE_ADIA));  
        //     } else { tap_code16(DE_ADIA); }
        //   set_last_keycode(DE_ADIA);
        //   register_mods(mods);  // Restore mods. 
        //   layer_off(SYMR); 
        //   return false;
        // case CKC_UDIA:      
        //   clear_oneshot_mods();  // Temporarily disable mods.
        //   unregister_mods(MOD_MASK_CSAG);  
        //   if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
        //     tap_code16(S(DE_UDIA));  
        //     } else { tap_code16(DE_UDIA); }
        //   set_last_keycode(DE_UDIA);
        //   register_mods(mods);  // Restore mods. 
        //   layer_off(SYMR); 
        //   return false;
        // case CKC_ODIA:      
        //   clear_oneshot_mods();  // Temporarily disable mods.
        //   unregister_mods(MOD_MASK_CSAG);  
        //   if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
        //     tap_code16(S(DE_ODIA));  
        //     } else { tap_code16(DE_ODIA); }
        //   set_last_keycode(DE_ODIA);
        //   register_mods(mods);  // Restore mods. 
        //   layer_off(SYMR); 
        //   return false;
        case CKC_EIN:      
          clear_oneshot_mods();  // Temporarily disable mods.
          unregister_mods(MOD_MASK_CSAG);  
          if ((mods | oneshot_mods) & MOD_MASK_SHIFT) {
              SEND_STRING("Ein");
            } else { SEND_STRING("ein"); }
          register_mods(mods);  // Restore mods.  
          break;         
      }      
    }
    return true;
}

void matrix_scan_user(void) {
    #ifdef ACHORDION_ENABLE
    achordion_task();
    #endif  // ACHORDION_ENABLE
    #ifdef LAYER_LOCK_ENABLE
    layer_lock_task();
    #endif  // LAYER_LOCK_ENABLE
    #ifdef SELECT_WORD_ENABLE
      select_word_task();
    #endif  // SELECT_WORD_ENABLE
    // Combos: prevent combos from firing during rolls
    // if (require_prior_idle_timer && timer_expired(timer_read(), require_prior_idle_timer)) {
    //   // If execution reaches here, the keyboard has gone idle.
    //   require_prior_idle_timer = 0;
    // }

    // Disable NAV layer after a configurable timeout
    if (get_highest_layer(layer_state) == NAV) {
      if (last_input_activity_elapsed() > NAV_LAYER_TIMEOUT) {
        layer_off(NAV);
      }
    }

    // set magic key to OSS after a configurable timeout
    if (last_input_activity_elapsed() > MAGIC_LAYER_TIMEOUT) {
      set_last_keycode(KC_SPC);
    }  
}
