#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "ssd1306.h"
#include "joystick.h"
#include "uart_log.h"

#define BUZZER_GPIO 10
#define LED_RGB_GPIO 7

#define IO_DELAY_MS 100

static uint32_t last_alert_time = 0;

static void buzzer_init(void) {
    gpio_init(BUZZER_GPIO);
    gpio_set_dir(BUZZER_GPIO, GPIO_OUT);
    gpio_put(BUZZER_GPIO, 0);
}

static void buzzer_beep(uint16_t duration_ms) {
    gpio_put(BUZZER_GPIO, 1);
    sleep_ms(duration_ms);
    gpio_put(BUZZER_GPIO, 0);
}

static void led_rgb_set(uint8_t r, uint8_t g, uint8_t b) {
    gpio_init(LED_RGB_GPIO);
    gpio_set_dir(LED_RGB_GPIO, GPIO_OUT);
    (void)r;
    (void)g;
    (void)b;
}

static void check_thresholds(uint16_t x, uint16_t y) {
    uint32_t now = to_ms_since_boot(get_absolute_time());
    
    if (x > 4000 || y > 4000 || x < 200 || y < 200) {
        if (now - last_alert_time > 500) {
            buzzer_beep(50);
            last_alert_time = now;
        }
    }
}

static void update_display(uint16_t x, uint16_t y, uint8_t joy_pressed, uint8_t btn_a, uint8_t btn_b) {
    ssd1306_clear();
    
    ssd1306_draw_text(0, 0, "Joystick:");
    ssd1306_draw_number(64, 0, x);
    
    ssd1306_draw_text(0, 16, "Y:");
    ssd1306_draw_number(16, 16, y);
    
    uint8_t y_btn = 32;
    if (joy_pressed) {
        ssd1306_draw_text(0, y_btn, "SW:PRESSIONADO!");
    } else {
        ssd1306_draw_text(0, y_btn, "SW:Solto");
    }
    
    if (btn_a) {
        ssd1306_draw_text(0, 48, "A:PRESSIONADO");
    }
    if (btn_b) {
        ssd1306_draw_text(72, 48, "B:PRESSIONADO");
    }
    
    ssd1306_update();
}

int main() {
    stdio_init_all();
    uart_log_init();
    uart_log("=== Monitor de Sensores com Alerta ===");
    
    i2c_init(i2c1, 400 * 1000);
    gpio_set_function(2, GPIO_FUNC_I2C);
    gpio_set_function(3, GPIO_FUNC_I2C);
    gpio_pull_up(2);
    gpio_pull_up(3);
    
    ssd1306_init(i2c1);
    uart_log("Display OLED inicializado");
    
    joystick_init();
    uart_log("Joystick inicializado");
    
    buttons_init();
    uart_log("Botoes inicializados");
    
    buzzer_init();
    uart_log("Buzzer inicializado");
    
    uart_log("Sistema pronto!");
    uart_log("Iniciando loop principal...");
    
    uint8_t btn_a_state = 0;
    uint8_t btn_b_state = 0;
    
    while (1) {
        uint16_t joy_x = joystick_read_x();
        uint16_t joy_y = joystick_read_y();
        uint8_t joy_sw = joystick_pressed();
        
        if (button_a_flag) {
            button_a_flag = 0;
            btn_a_state = !btn_a_state;
            uart_log("Botao A pressionado!");
            buzzer_beep(100);
        }
        
        if (button_b_flag) {
            button_b_flag = 0;
            btn_b_state = !btn_b_state;
            uart_log("Botao B pressionado!");
            buzzer_beep(150);
        }
        
        check_thresholds(joy_x, joy_y);
        
        uart_log_int("JoyX", joy_x);
        uart_log_int("JoyY", joy_y);
        
        update_display(joy_x, joy_y, joy_sw, btn_a_state, btn_b_state);
        
        sleep_ms(IO_DELAY_MS);
    }
    
    return 0;
}