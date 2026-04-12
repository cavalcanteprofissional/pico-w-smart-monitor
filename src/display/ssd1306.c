#include "ssd1306.h"
#include "hardware/i2c.h"
#include <string.h>
#include "font.h"

static i2c_inst_t *ssd1306_i2c = NULL;

uint8_t ssd1306_buffer[SSD1306_HEIGHT / 8][SSD1306_WIDTH];

static void ssd1306_command(uint8_t cmd) {
    uint8_t buf[2] = {0x00, cmd};
    i2c_write_blocking(ssd1306_i2c, SSD1306_I2C_ADDR, buf, 2, false);
}

static void ssd1306_data(uint8_t data) {
    uint8_t buf[2] = {0x40, data};
    i2c_write_blocking(ssd1306_i2c, SSD1306_I2C_ADDR, buf, 2, false);
}

void ssd1306_init(i2c_inst_t *i2c) {
    ssd1306_i2c = i2c;
    
    ssd1306_command(SSD1306_SET_DISP | 0x00);
    ssd1306_command(SSD1306_SET_MEM_ADDR);
    ssd1306_command(0x00);
    ssd1306_command(SSD1306_SET_DISP_START_LINE | 0x00);
    ssd1306_command(SSD1306_SET_SEG_REMAP | 0x01);
    ssd1306_command(SSD1306_SET_MUX_RATIO);
    ssd1306_command(SSD1306_HEIGHT - 1);
    ssd1306_command(SSD1306_SET_COM_OUT_DIR | 0x08);
    ssd1306_command(SSD1306_SET_COM_CONFIG);
    ssd1306_command(0x12);
    ssd1306_command(SSD1306_SET_DCLK);
    ssd1306_command(0x80);
    ssd1306_command(SSD1306_SET_PRECHARGE);
    ssd1306_command(0xF1);
    ssd1306_command(SSD1306_SET_VCOM_DESEL);
    ssd1306_command(0x30);
    ssd1306_command(SSD1306_SET_CHARGE_PUMP);
    ssd1306_command(0x14);
    ssd1306_command(SSD1306_SET_ENTIRE_ON);
    ssd1306_command(SSD1306_SET_NORM_INV);
    ssd1306_command(SSD1306_SET_CONTRAST);
    ssd1306_command(0xFF);
    ssd1306_command(SSD1306_SET_DISP | 0x01);
    
    ssd1306_clear();
    ssd1306_update();
}

void ssd1306_clear(void) {
    memset(ssd1306_buffer, 0, sizeof(ssd1306_buffer));
}

void ssd1306_update(void) {
    ssd1306_command(SSD1306_SET_COL_ADDR);
    ssd1306_command(0x00);
    ssd1306_command(SSD1306_WIDTH - 1);
    ssd1306_command(SSD1306_SET_PAGE_ADDR);
    ssd1306_command(0x00);
    ssd1306_command((SSD1306_HEIGHT / 8) - 1);

    for (uint8_t page = 0; page < SSD1306_HEIGHT / 8; page++) {
        for (uint8_t col = 0; col < SSD1306_WIDTH; col++) {
            ssd1306_data(ssd1306_buffer[page][col]);
        }
    }
}

void ssd1306_draw_pixel(uint8_t x, uint8_t y, uint8_t color) {
    if (x >= SSD1306_WIDTH || y >= SSD1306_HEIGHT) return;
    
    uint8_t page = y / 8;
    uint8_t bit = y % 8;
    
    if (color) {
        ssd1306_buffer[page][x] |= (1 << bit);
    } else {
        ssd1306_buffer[page][x] &= ~(1 << bit);
    }
}

void ssd1306_draw_char(uint8_t x, uint8_t y, char c) {
    if (c < 32 || c > 126) c = 32;
    
    const uint8_t *glyph = font_5x8[c - 32];
    
    for (uint8_t i = 0; i < 5; i++) {
        uint8_t col = glyph[i];
        for (uint8_t j = 0; j < 8; j++) {
            if (col & (1 << j)) {
                ssd1306_draw_pixel(x + i, y + j, 1);
            }
        }
    }
}

void ssd1306_draw_text(uint8_t x, uint8_t y, const char *str) {
    uint8_t cursor_x = x;
    
    while (*str) {
        ssd1306_draw_char(cursor_x, y, *str);
        cursor_x += 6;
        str++;
        
        if (cursor_x >= SSD1306_WIDTH - 5) break;
    }
}

void ssd1306_draw_number(uint8_t x, uint8_t y, int16_t value) {
    char buffer[8];
    int8_t len = 0;
    
    if (value < 0) {
        buffer[len++] = '-';
        value = -value;
    }
    
    if (value == 0) {
        buffer[len++] = '0';
    } else {
        uint8_t temp[8];
        uint8_t idx = 0;
        
        while (value > 0) {
            temp[idx++] = '0' + (value % 10);
            value /= 10;
        }
        
        for (int8_t i = idx - 1; i >= 0; i--) {
            buffer[len++] = temp[i];
        }
    }
    
    buffer[len] = '\0';
    ssd1306_draw_text(x, y, buffer);
}

void ssd1306_draw_hline(uint8_t x, uint8_t y, uint8_t w) {
    for (uint8_t i = 0; i < w; i++) {
        if (x + i < SSD1306_WIDTH) {
            ssd1306_draw_pixel(x + i, y, 1);
        }
    }
}

void ssd1306_draw_vline(uint8_t x, uint8_t y, uint8_t h) {
    for (uint8_t i = 0; i < h; i++) {
        if (y + i < SSD1306_HEIGHT) {
            ssd1306_draw_pixel(x, y + i, 1);
        }
    }
}

void ssd1306_draw_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h) {
    ssd1306_draw_hline(x, y, w);
    ssd1306_draw_hline(x, y + h - 1, w);
    ssd1306_draw_vline(x, y, h);
    ssd1306_draw_vline(x + w - 1, y, h);
}