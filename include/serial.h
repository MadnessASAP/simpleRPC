#pragma once

#include <stddef.h>
#include <stdint.h>

#ifndef SERIAL_USART_INDEX
#define SERIAL_USART_INDEX 0
#endif

void serial_init(uint32_t baud);
size_t serial_write(uint8_t const* data, size_t len);
size_t serial_write_byte(uint8_t byte);
int serial_available();
uint8_t serial_read_byte();
