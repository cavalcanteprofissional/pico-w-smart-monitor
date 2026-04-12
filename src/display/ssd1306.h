#ifndef SSD1306_H
#define SSD1306_H

#include <stdint.h>
#include "hardware/i2c.h"

#define SSD1306_I2C_ADDR 0x3D
#define SSD1306_WIDTH 128
#define SSD1306_HEIGHT 64

#define SSD1306_SET_CONTRAST 0x81
#define SSD1306_SET_ENTIRE_ON 0xA4
#define SSD1306_SET_NORM_INV 0xA6
#define SSD1306_SET_DISP 0xAE
#define SSD1306_SET_MEM_ADDR 0x20
#define SSD1306_SET_COL_ADDR 0x21
#define SSD1306_SET_PAGE_ADDR 0x22
#define SSD1306_SET_DISP_START_LINE 0x40
#define SSD1306_SET_SEG_REMAP 0xA0
#define SSD1306_SET_MUX_RATIO 0xA8
#define SSD1306_SET_COM_OUT_DIR 0xC0
#define SSD1306_SET_COM_CONFIG 0xDA
#define SSD1306_SET_DCLK 0xD5
#define SSD1306_SET_PRECHARGE 0xD9
#define SSD1306_SET_COM_ALT 0xDA
#define SSD1306_SET_VCOM_DESEL 0xDB
#define SSD1306_SET_CHARGE_PUMP 0x8D

void ssd1306_init(i2c_inst_t *i2c);
void ssd1306_clear(void);
void ssd1306_update(void);
void ssd1306_draw_pixel(uint8_t x, uint8_t y, uint8_t color);
void ssd1306_draw_char(uint8_t x, uint8_t y, char c);
void ssd1306_draw_text(uint8_t x, uint8_t y, const char *str);
void ssd1306_draw_number(uint8_t x, uint8_t y, int16_t value);
void ssd1306_draw_hline(uint8_t x, uint8_t y, uint8_t w);
void ssd1306_draw_vline(uint8_t x, uint8_t y, uint8_t h);
void ssd1306_draw_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h);

extern uint8_t ssd1306_buffer[SSD1306_HEIGHT / 8][SSD1306_WIDTH];

#endif