#include "uart_log.h"
#include "hardware/uart.h"
#include "pico/stdlib.h"
#include <string.h>

static uart_inst_t *uart_log_uart = NULL;

void uart_log_init(void) {
    uart_init(uart0, 115200);
    gpio_set_function(0, GPIO_FUNC_UART);
    gpio_set_function(1, GPIO_FUNC_UART);
    uart_log_uart = uart0;
}

void uart_log(const char *msg) {
    if (uart_log_uart) {
        uart_puts(uart_log_uart, msg);
        uart_puts(uart_log_uart, "\r\n");
    }
}

void uart_log_int(const char *label, int16_t value) {
    if (!uart_log_uart) return;
    
    char buffer[32];
    int idx = 0;
    
    while (*label && idx < 31) {
        buffer[idx++] = *label++;
    }
    buffer[idx++] = ':';
    buffer[idx++] = ' ';
    
    if (value < 0) {
        buffer[idx++] = '-';
        value = -value;
    }
    
    if (value == 0) {
        buffer[idx++] = '0';
    } else {
        char temp[8];
        uint8_t tidx = 0;
        while (value > 0) {
            temp[tidx++] = '0' + (value % 10);
            value /= 10;
        }
        while (tidx > 0) {
            buffer[idx++] = temp[--tidx];
        }
    }
    
    buffer[idx++] = '\r';
    buffer[idx++] = '\n';
    buffer[idx] = '\0';
    
    uart_write_blocking(uart_log_uart, (const uint8_t *)buffer, idx);
}

void uart_log_hex(const char *label, uint8_t value) {
    if (!uart_log_uart) return;
    
    char buffer[32];
    int idx = 0;
    
    while (*label && idx < 31) {
        buffer[idx++] = *label++;
    }
    buffer[idx++] = ':';
    buffer[idx++] = ' ';
    
    const char *hex_chars = "0123456789ABCDEF";
    buffer[idx++] = hex_chars[(value >> 4) & 0x0F];
    buffer[idx++] = hex_chars[value & 0x0F];
    buffer[idx++] = '\r';
    buffer[idx++] = '\n';
    buffer[idx] = '\0';
    
    uart_write_blocking(uart_log_uart, (const uint8_t *)buffer, idx);
}