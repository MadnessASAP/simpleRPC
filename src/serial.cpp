#include "serial.h"

#if !defined(ARDUINO)
#include <avr/io.h>

#if SERIAL_USART_INDEX == 0
#define SERIAL_UBRRH UBRR0H
#define SERIAL_UBRRL UBRR0L
#define SERIAL_UCSRA UCSR0A
#define SERIAL_UCSRB UCSR0B
#define SERIAL_UCSRC UCSR0C
#define SERIAL_UDR UDR0
#define SERIAL_RXEN RXEN0
#define SERIAL_TXEN TXEN0
#define SERIAL_UCSZ0 UCSZ00
#define SERIAL_UCSZ1 UCSZ01
#define SERIAL_UDRE UDRE0
#define SERIAL_RXC RXC0
#elif SERIAL_USART_INDEX == 1
#if !defined(UBRR1H)
#error "SERIAL_USART_INDEX=1 but USART1 registers are not available on this MCU."
#endif
#define SERIAL_UBRRH UBRR1H
#define SERIAL_UBRRL UBRR1L
#define SERIAL_UCSRA UCSR1A
#define SERIAL_UCSRB UCSR1B
#define SERIAL_UCSRC UCSR1C
#define SERIAL_UDR UDR1
#define SERIAL_RXEN RXEN1
#define SERIAL_TXEN TXEN1
#define SERIAL_UCSZ0 UCSZ10
#define SERIAL_UCSZ1 UCSZ11
#define SERIAL_UDRE UDRE1
#define SERIAL_RXC RXC1
#elif SERIAL_USART_INDEX == 2
#if !defined(UBRR2H)
#error "SERIAL_USART_INDEX=2 but USART2 registers are not available on this MCU."
#endif
#define SERIAL_UBRRH UBRR2H
#define SERIAL_UBRRL UBRR2L
#define SERIAL_UCSRA UCSR2A
#define SERIAL_UCSRB UCSR2B
#define SERIAL_UCSRC UCSR2C
#define SERIAL_UDR UDR2
#define SERIAL_RXEN RXEN2
#define SERIAL_TXEN TXEN2
#define SERIAL_UCSZ0 UCSZ20
#define SERIAL_UCSZ1 UCSZ21
#define SERIAL_UDRE UDRE2
#define SERIAL_RXC RXC2
#elif SERIAL_USART_INDEX == 3
#if !defined(UBRR3H)
#error "SERIAL_USART_INDEX=3 but USART3 registers are not available on this MCU."
#endif
#define SERIAL_UBRRH UBRR3H
#define SERIAL_UBRRL UBRR3L
#define SERIAL_UCSRA UCSR3A
#define SERIAL_UCSRB UCSR3B
#define SERIAL_UCSRC UCSR3C
#define SERIAL_UDR UDR3
#define SERIAL_RXEN RXEN3
#define SERIAL_TXEN TXEN3
#define SERIAL_UCSZ0 UCSZ30
#define SERIAL_UCSZ1 UCSZ31
#define SERIAL_UDRE UDRE3
#define SERIAL_RXC RXC3
#else
#error "Unsupported SERIAL_USART_INDEX (valid: 0-3)."
#endif

void serial_init(uint32_t baud) {
  uint16_t ubrr {static_cast<uint16_t>((F_CPU / (16UL * baud)) - 1U)};

  SERIAL_UBRRH = static_cast<uint8_t>(ubrr >> 8);
  SERIAL_UBRRL = static_cast<uint8_t>(ubrr);

  SERIAL_UCSRA = 0;
  SERIAL_UCSRB = static_cast<uint8_t>((1U << SERIAL_RXEN) | (1U << SERIAL_TXEN));
  SERIAL_UCSRC = static_cast<uint8_t>((1U << SERIAL_UCSZ1) | (1U << SERIAL_UCSZ0));
}

size_t serial_write_byte(uint8_t byte) {
  while ((SERIAL_UCSRA & static_cast<uint8_t>(1U << SERIAL_UDRE)) == 0) {
  }
  SERIAL_UDR = byte;
  return 1;
}

size_t serial_write(uint8_t const* data, size_t len) {
  size_t written {0};
  for (size_t i {0}; i < len; ++i) {
    written += serial_write_byte(data[i]);
  }
  return written;
}

int serial_available() {
  return (SERIAL_UCSRA & static_cast<uint8_t>(1U << SERIAL_RXC)) ? 1 : 0;
}

uint8_t serial_read_byte() {
  while (!serial_available()) {
  }
  return SERIAL_UDR;
}
#endif
