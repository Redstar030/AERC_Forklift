/**
 * @file controller.c
 * @author Lau Chun Ting, Justin (Justin610810@outlook.com)
 * @brief Decode PS4 controller input data from a string format
 * @version 1.0
 * @date 2025-08-07
 *
 * @copyright Copyright (c) 2025
 *
 */

#include "ps4.h"

char controller_buffer[CONTROLLER_BUFFER_SIZE] = "";

ControllerState controller_state = {.r1 = false, .r2 = false, .r3 = false, .l1 = false, .l2 = false, .l3 = false, .cross = false, .circle = false, .triangle = false, .square = false, .up = false, .down = false, .left = false, .right = false, .l_stick_x = 0, .l_stick_y = 0, .r_stick_x = 0, .r_stick_y = 0, .l2_pressure = 0, .r2_pressure = 0, .ps_button = false, .share_button = false, .options_button = false};

uint8_t parse_controller_data(const char* input, ControllerState* data) {
  if (input == NULL || data == NULL) {
    printf("Invalid input or data pointer\n");
    return 1;
  }

  int dpad_value;
  int buttons_value;
  char l_stick_x_str[5], l_stick_y_str[5], r_stick_x_str[5], r_stick_y_str[5];
  int l2_pressure, r2_pressure;
  int misc_buttons;

  int parse_num = sscanf(input, "c:%1x,%03x,%4s,%4s,%4s,%4s,%d,%d,%1x", &dpad_value, &buttons_value, l_stick_y_str, l_stick_x_str, r_stick_y_str, r_stick_x_str, &l2_pressure, &r2_pressure, &misc_buttons);

  if (parse_num != 9) {
    printf("Error parsing input string\n");
    return 2;
  }

  data->up = dpad_value & 0x1;
  data->down = dpad_value & 0x2;
  data->right = dpad_value & 0x4;
  data->left = dpad_value & 0x8;

  data->cross = buttons_value & 0x001;
  data->circle = buttons_value & 0x002;
  data->square = buttons_value & 0x004;
  data->triangle = buttons_value & 0x008;
  data->l1 = buttons_value & 0x010;
  data->r1 = buttons_value & 0x020;
  data->l2 = buttons_value & 0x040;
  data->r2 = buttons_value & 0x080;
  data->l3 = buttons_value & 0x100;
  data->r3 = buttons_value & 0x200;

  data->l_stick_y = (int8_t)strtol(l_stick_y_str, NULL, 10);
  data->l_stick_x = (int8_t)strtol(l_stick_x_str, NULL, 10);
  data->r_stick_y = (int8_t)strtol(r_stick_y_str, NULL, 10);
  data->r_stick_x = (int8_t)strtol(r_stick_x_str, NULL, 10);

  data->l2_pressure = (uint16_t)l2_pressure;
  data->r2_pressure = (uint16_t)r2_pressure;

  data->ps_button = misc_buttons & 0x1;
  data->share_button = misc_buttons & 0x2;
  data->options_button = misc_buttons & 0x4;

  return 0;
}