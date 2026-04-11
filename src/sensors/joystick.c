#include "joystick.h"
#include "hardware/gpio.h"
#include "hardware/adc.h"
#include "pico/stdlib.h"

volatile uint8_t button_a_flag = 0;
volatile uint8_t button_b_flag = 0;

void joystick_init(void) {
    adc_init();
    adc_gpio_init(JOYSTICK_VRX_GPIO);
    adc_gpio_init(JOYSTICK_VRY_GPIO);
    gpio_init(JOYSTICK_SW_GPIO);
    gpio_set_dir(JOYSTICK_SW_GPIO, GPIO_IN);
    gpio_pull_up(JOYSTICK_SW_GPIO);
}

uint16_t joystick_read_x(void) {
    adc_select_input(0);
    return adc_read();
}

uint16_t joystick_read_y(void) {
    adc_select_input(1);
    return adc_read();
}

uint8_t joystick_pressed(void) {
    return gpio_get(JOYSTICK_SW_GPIO) == 0;
}

static void button_a_isr(uint gpio, uint32_t events) {
    (void)gpio;
    (void)events;
    button_a_flag = 1;
}

static void button_b_isr(uint gpio, uint32_t events) {
    (void)gpio;
    (void)events;
    button_b_flag = 1;
}

void buttons_init(void) {
    gpio_init(BUTTON_A_GPIO);
    gpio_init(BUTTON_B_GPIO);
    gpio_set_dir(BUTTON_A_GPIO, GPIO_IN);
    gpio_set_dir(BUTTON_B_GPIO, GPIO_IN);
    gpio_pull_up(BUTTON_A_GPIO);
    gpio_pull_up(BUTTON_B_GPIO);
    
    gpio_set_irq_enabled_with_callback(BUTTON_A_GPIO, GPIO_IRQ_EDGE_FALL, true, &button_a_isr);
    gpio_set_irq_enabled_with_callback(BUTTON_B_GPIO, GPIO_IRQ_EDGE_FALL, true, &button_b_isr);
}

uint8_t button_a_pressed(void) {
    return gpio_get(BUTTON_A_GPIO) == 0;
}

uint8_t button_b_pressed(void) {
    return gpio_get(BUTTON_B_GPIO) == 0;
}