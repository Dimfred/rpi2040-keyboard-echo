#include <class/hid/hid_device.h>
#include <device/usbd.h>
#include <pico/stdlib.h>
#include <stdio.h>
#include <string.h>
#include <tusb.h>

// HID Keycodes (subset - add more as needed)
#define HID_KEY_A 0x04
#define HID_KEY_B 0x05
#define HID_KEY_C 0x06
#define HID_KEY_D 0x07
#define HID_KEY_E 0x08
#define HID_KEY_F 0x09
#define HID_KEY_G 0x0A
#define HID_KEY_H 0x0B
#define HID_KEY_I 0x0C
#define HID_KEY_J 0x0D
#define HID_KEY_K 0x0E
#define HID_KEY_L 0x0F
#define HID_KEY_M 0x10
#define HID_KEY_N 0x11
#define HID_KEY_O 0x12
#define HID_KEY_P 0x13
#define HID_KEY_Q 0x14
#define HID_KEY_R 0x15
#define HID_KEY_S 0x16
#define HID_KEY_T 0x17
#define HID_KEY_U 0x18
#define HID_KEY_V 0x19
#define HID_KEY_W 0x1A
#define HID_KEY_X 0x1B
#define HID_KEY_Y 0x1C
#define HID_KEY_Z 0x1D
#define HID_KEY_1 0x1E
#define HID_KEY_2 0x1F
#define HID_KEY_3 0x20
#define HID_KEY_4 0x21
#define HID_KEY_5 0x22
#define HID_KEY_6 0x23
#define HID_KEY_7 0x24
#define HID_KEY_8 0x25
#define HID_KEY_9 0x26
#define HID_KEY_0 0x27
#define HID_KEY_ENTER 0x28
#define HID_KEY_SPACE 0x2C

#define KEYBOARD_MODIFIER_LEFTSHIFT 0x02

// Map ASCII to HID keycode
uint8_t ascii_to_keycode(char c) {
  if (c >= 'a' && c <= 'z')
    return HID_KEY_A + (c - 'a');
  if (c >= 'A' && c <= 'Z')
    return HID_KEY_A + (c - 'A');
  if (c >= '1' && c <= '9')
    return HID_KEY_1 + (c - '1');
  if (c == '0')
    return HID_KEY_0;
  if (c == ' ')
    return HID_KEY_SPACE;
  if (c == '\n' || c == '\r')
    return HID_KEY_ENTER;
  return 0;
}

// Check if character needs shift modifier
bool needs_shift(char c) { return (c >= 'A' && c <= 'Z'); }

void send_key(char c) {
  uint8_t keycode = ascii_to_keycode(c);
  if (keycode == 0)
    return;

  uint8_t modifier = needs_shift(c) ? KEYBOARD_MODIFIER_LEFTSHIFT : 0;
  uint8_t keycode_array[6] = {keycode, 0, 0, 0, 0, 0};

  // Send key press
  tud_hid_keyboard_report(1, modifier, keycode_array);
  sleep_ms(10);

  // Send key release
  tud_hid_keyboard_report(1, 0, NULL);
  sleep_ms(10);
}

int main() {
  stdio_init_all();
  tusb_init();

  printf("USB Keyboard ready!\n");

  while (1) {
    tud_task(); // TinyUSB device task

    // Check for incoming serial data
    int c = getchar_timeout_us(0);
    if (c != PICO_ERROR_TIMEOUT) {
      char ch = (char)c;

      // Send as keyboard input
      send_key(ch);

      // Echo back confirmation
      printf("Sent: %c\n", ch);
    }
  }

  return 0;
}

// TinyUSB HID callbacks
uint16_t tud_hid_get_report_cb(uint8_t instance, uint8_t report_id,
                               hid_report_type_t report_type, uint8_t *buffer,
                               uint16_t reqlen) {
  return 0;
}

void tud_hid_set_report_cb(uint8_t instance, uint8_t report_id,
                           hid_report_type_t report_type, uint8_t const *buffer,
                           uint16_t bufsize) {}
