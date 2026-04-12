#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/i2c.h"
#include "hardware/gpio.h"
#include "ssd1306.h"
#include "joystick.h"

#define BUZZER_GPIO 10

#define IO_DELAY_MS 100

static uint32_t last_alert_time = 0;

static void buzzer_init(void) {
    gpio_init(BUZZER_GPIO);
    gpio_set_dir(BUZZER_GPIO, GPIO_OUT);
    gpio_put(BUZZER_GPIO, 0);
    printf("[DEBUG] Buzzer inicializado no GPIO%d\n", BUZZER_GPIO);
}

static void buzzer_beep(uint16_t duration_ms) {
    gpio_put(BUZZER_GPIO, 1);
    sleep_ms(duration_ms);
    gpio_put(BUZZER_GPIO, 0);
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
    
    ssd1306_draw_text(0, 0, "X:");
    ssd1306_draw_number(16, 0, x);
    
    ssd1306_draw_text(0, 16, "Y:");
    ssd1306_draw_number(16, 16, y);
    
    if (joy_pressed) {
        ssd1306_draw_text(0, 32, "SW:PRESS");
    } else {
        ssd1306_draw_text(0, 32, "SW:Livre");
    }
    
    if (btn_a) {
        ssd1306_draw_text(0, 48, "A:OK");
    }
    if (btn_b) {
        ssd1306_draw_text(40, 48, "B:OK");
    }
    
    ssd1306_update();
}

int main() {
    printf("\n=== INICIO DO SISTEMA ===\n");
    printf("Versao: 1.1 - Debug\n");
    
    printf("[1] Inicializando stdio USB...\n");
    stdio_init_all();
    printf("[OK] stdio USB\n");
    
    printf("[2] Inicializando I2C (GPIO2=SDA, GPIO3=SCL)...\n");
    i2c_init(i2c1, 400 * 1000);
    gpio_set_function(2, GPIO_FUNC_I2C);
    gpio_set_function(3, GPIO_FUNC_I2C);
    gpio_pull_up(2);
    gpio_pull_up(3);
    printf("[OK] I2C\n");
    
    printf("[3] Inicializando Display OLED...\n");
    ssd1306_init(i2c1);
    printf("[OK] Display OLED\n");
    
    printf("[4] Inicializando Joystick...\n");
    joystick_init();
    printf("[OK] Joystick\n");
    
    printf("[5] Inicializando Buttons...\n");
    buttons_init();
    printf("[OK] Buttons\n");
    
    printf("[6] Inicializando Buzzer...\n");
    buzzer_init();
    printf("[OK] Buzzer\n");
    
    printf("\n=== SISTEMA PRONTO ===\n");
    printf("Loop principal iniciando...\n\n");
    
    uint8_t btn_a_state = 0;
    uint8_t btn_b_state = 0;
    
    while (1) {
        uint16_t joy_x = joystick_read_x();
        uint16_t joy_y = joystick_read_y();
        uint8_t joy_sw = joystick_pressed();
        
        if (button_a_flag) {
            button_a_flag = 0;
            btn_a_state = !btn_a_state;
            printf("Botao A: toggle -> %d\n", btn_a_state);
            buzzer_beep(100);
        }
        
        if (button_b_flag) {
            button_b_flag = 0;
            btn_b_state = !btn_b_state;
            printf("Botao B: toggle -> %d\n", btn_b_state);
            buzzer_beep(150);
        }
        
        check_thresholds(joy_x, joy_y);
        
        printf("X:%4d Y:%4d\n", joy_x, joy_y);
        
        update_display(joy_x, joy_y, joy_sw, btn_a_state, btn_b_state);
        
        sleep_ms(IO_DELAY_MS);
    }
    
    return 0;
}