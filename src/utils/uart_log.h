#ifndef UART_LOG_H
#define UART_LOG_H

#include <stdint.h>

void uart_log_init(void);
void uart_log(const char *msg);
void uart_log_int(const char *label, int16_t value);
void uart_log_hex(const char *label, uint8_t value);

#endif