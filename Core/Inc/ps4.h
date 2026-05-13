/**
 * @file controller.h
 * @author Lau Chun Ting, Justin (Justin610810@outlook.com)
 * @brief Decode PS4 controller input data from a string format
 * @version 1.0
 * @date 2025-08-07
 *
 * @copyright Copyright (c) 2025
 *
 */

/**
 * Remember to include the following libraries in your project:
 * - [] <stdbool.h> for boolean type definitions
 * - [] <stdint.h> for fixed-width integer types
 * - [] <stdio.h> for standard input/output functions
 * - [] <string.h> for string manipulation functions
 *
 */

/**
 * Before using this file, make sure to define the following macros in your project:
 * - [] CONTROLLER_BUFFER_SIZE: the size of the controller buffer, e.g., 41
 *
 */

/**
 * The input string format is: c:%1x,%03x,%s,%s,%s,%s,%s,%s,%1x\n
 * e.g. c:1,1cc,+076,-076,+078,-074,1020,1020,3\n
 * %1x - Dpad value (1 byte)
 *  - 0x1 - Up
 *  - 0x2 - Down
 *  - 0x4 - Right
 *  - 0x8 - Left
 *  - value can be sum of these values
 * %03x - Buttons value (3 bytes)
 *  - 0x001 - Cross
 *  - 0x002 - Circle
 *  - 0x004 - Square
 *  - 0x008 - Triangle
 *  - 0x010 - L1
 *  - 0x020 - R1
 *  - 0x040 - L2
 *  - 0x080 - R2
 *  - 0x100 - L3
 *  - 0x200 - R3
 * 1st %s - Axis data (4 strings)
 *  - %s - Left stick X axis value (3 bytes)
 *  - the first character is '+' or '-' depending on the sign
 *  - the next 3 characters are the absolute value of the axis value
 * 2nd %s - Axis data (4 strings)
 *  - %s - Left stick Y axis value (3 bytes)
 *  - the first character is '+' or '-' depending on the sign
 *  - the next 3 characters are the absolute value of the axis value
 * 3rd %s - Axis data (4 strings)
 *  - %s - Right stick X axis value (3 bytes)
 *  - the first character is '+' or '-' depending on the sign
 *  - the next 3 characters are the absolute value of the axis value
 * 4th %s - Axis data (4 strings)
 *  - %s - Right stick Y axis value (3 bytes)
 *  - the first character is '+' or '-' depending on the sign
 *  - the next 3 characters are the absolute value of the axis value
 * 5th %s - Brake value (4 strings)
 *  - the pressure value of L2 button
 * 6th %s - Throttle value (4 strings)
 *  - the pressure value of R2 button
 * %1x - Misc buttons value (1 byte)
 *  - 0x1 - PS button
 *  - 0x2 - share button
 *  - 0x4 - options button
 */

#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__

#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#define CONTROLLER_BUFFER_SIZE 41

typedef struct {
  bool r1;
  bool r2;
  bool r3;
  bool l1;
  bool l2;
  bool l3;
  bool cross;
  bool circle;
  bool triangle;
  bool square;
  bool up;
  bool down;
  bool left;
  bool right;
  int8_t l_stick_x;
  int8_t l_stick_y;
  int8_t r_stick_x;
  int8_t r_stick_y;
  uint16_t l2_pressure;
  uint16_t r2_pressure;
  bool ps_button;
  bool share_button;
  bool options_button;
} ControllerState;

/**
 * @brief Parses the input string to extract controller state data.
 *
 * This function takes an input string and parses it to populate the
 * provided ControllerState structure with relevant data. It returns
 * a status code indicating the success or failure of the operation.
 *
 * @param input A pointer to the input string containing the controller data.
 * @param data A pointer to the ControllerState structure to be populated.
 * @return uint8_t Returns 0 on success, or an error code on failure.
 */
uint8_t parse_controller_data(const char* input, ControllerState* data);

extern char controller_buffer[CONTROLLER_BUFFER_SIZE];
extern ControllerState controller_state;

#endif  // __CONTROLLER_H__