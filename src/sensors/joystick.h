#ifndef JOYSTICK_H
#define JOYSTICK_H

#include <stdint.h>
#include "hardware/adc.h"

#define JOYSTICK_VRX_GPIO 26
#define JOYSTICK_VRY_GPIO 27
#define JOYSTICK_SW_GPIO 22

#define BUTTON_A_GPIO 5
#define BUTTON_B_GPIO 6

void joystick_init(void);
uint16_t joystick_read_x(void);
uint16_t joystick_read_y(void);
uint8_t joystick_pressed(void);

void buttons_init(void);
uint8_t button_a_pressed(void);
uint8_t button_b_pressed(void);

extern volatile uint8_t button_a_flag;
extern volatile uint8_t button_b_flag;

#endif