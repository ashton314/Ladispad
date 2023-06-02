#include "ladis.h"
#include QMK_KEYBOARD_H

#define _BL 0
#define _FL 1

enum custom_keycodes {
  INBOXEMAIL = SAFE_RANGE,
  DEVEMAIL,
  SCHOOLEMAIL
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  switch (keycode) {
  case INBOXEMAIL:
    if (record->event.pressed) {
      SEND_STRING("inbox@wiersdorfmail.net");
    } else {
      // when keycode is released
    }
    break;
  case DEVEMAIL:
    if (record->event.pressed) {
      SEND_STRING("mail@wiersdorf.dev");
    } else {
      // when keycode is released
    }
    break;
  case SCHOOLEMAIL:
    if (record->event.pressed) {
      SEND_STRING("ashton.wiersdorf@utah.edu");
    } else {
      // when keycode is released
    }
    break;
  }
  return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

  [_BL] = LAYOUT(
                 KC_MEDIA_PREV_TRACK, KC_MEDIA_PLAY_PAUSE, KC_MEDIA_NEXT_TRACK, \
                 KC_MISSION_CONTROL, LSG(KC_5), HYPR(KC_SPACE), \
                 LSG(KC_A), LSG(KC_V), MO(_FL),
                 KC_NO, KC_MUTE
                 ),

  [_FL] = LAYOUT(
                 QK_BOOTLOADER, C(A(G(KC_R))), C(A(G(KC_S))), \
                 SCHOOLEMAIL, C(A(G(KC_H))), C(A(G(KC_F))), \
                 INBOXEMAIL, DEVEMAIL, KC_NO, \
                 KC_NO, KC_NO),

};

bool encoder_update_user(uint8_t index, bool clockwise) {
  if (index == 0) { /* First encoder */
    if (clockwise & layer_state_is(_BL)) {
      tap_code(KC_RIGHT);
    } else if (clockwise & layer_state_is(_FL)){
      tap_code(KC_MS_WH_UP);
    }
    else if (!clockwise & layer_state_is(_BL)){
      tap_code(KC_LEFT);
    }
    else if (!clockwise & layer_state_is(_FL)) {
      tap_code(KC_MS_WH_DOWN);
    }
  } else if (index == 1) { /* Second encoder */
    if (clockwise & layer_state_is(_BL)) {
      tap_code(KC_AUDIO_VOL_UP);
    } else if (clockwise & layer_state_is(_FL)){
      tap_code(KC_MS_WH_RIGHT);
    }

    else if (!clockwise & layer_state_is(_BL)){
      tap_code(KC_AUDIO_VOL_DOWN);
    }
    else if (!clockwise & layer_state_is(_FL)) {
      tap_code(KC_MS_WH_LEFT);
    }
  }
  return false;
}

/* static void render_logo(void) { */
/*   static const char PROGMEM raw_logo[] = { */
/*     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, 31,127,255,255,255,255,255, 31, 15,  7,  7,  7,  3,  3,  3,  3,  3,  7,  7,  7, 15, 63,255,255,255,255,255,255,  3,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,224,224,240,112,112,240,240,224,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,240,240,192,  0,  0,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, */
/*     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  3,127,255,255,255,255,254,252,252,252,252,124, 56,124,252,252,252,254,254,254,255,255,255,255, 63,  1,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  7,  7,  1,192,248,255,255, 15,  1,128,192,224,224,240,112,176, 32,  0,  0,  0,128,192,224,240,112, 48, 32,224,252,255,127,  7,192,240,231,  7,  7,224,224,240, 48, 48,240,224, 64,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, */
/*     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,128,255,255,255,255,255,223,135,135,191,248,112,112,187,135,  7,135,143,255,255,255,255,251,128,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,192,192,224,252,255,191,135,  0, 16,254,255,199,227,112, 60,254,255, 63,  6,  0,126,255,255,195,240, 56,124,255,255, 31,  3, 32,252,255, 63,  7,112,240,225,199,207,255,252,120,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, */
/*     0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,248,255,255,255,255,255,255,255,255,255,253,253,253,252,252,253,255,255,255,255,255,255,255,255,255,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  1,  1,  3,  3,  7,  7, 15, 14, 30, 30, 28, 28, 14,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0,  0, */
/*   }; */
/*   oled_write_raw_P(raw_logo, sizeof(raw_logo)); */
/* } */


bool oled_task_user(void) {
  /* if (is_keyboard_master()) { */
  /*   // If you want to put your image on the master side, put your function call here: */
  /*   render_logo(); */
  /* } else { */
  /*   // And if you want to put your image on the slave side, put it here instead: */
  /*   render_logo(); */
  /* } */

  oled_write_P(PSTR("Layer: "), false);

  switch (get_highest_layer(layer_state)) {
  case _BL:
    oled_write_P(PSTR("Base layer\n"), false);
    break;
  case _FL:
    oled_write_P(PSTR("Second layer\n"), false);
    break;
  default:
    // Or use the write_ln shortcut over adding '\n' to the end of your string
    oled_write_ln_P(PSTR("Undefined"), false);
  }

  // Host Keyboard LED Status
  /* led_t led_state = host_keyboard_led_state(); */
  /* oled_write_P(led_state.num_lock ? PSTR("NUM ") : PSTR("    "), false); */
  /* oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false); */
  /* oled_write_P(led_state.scroll_lock ? PSTR("SCR ") : PSTR("    "), false); */

  return false;
}
