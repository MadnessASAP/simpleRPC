#include "stream.h"

#if !defined(ARDUINO)
#include "serial.h"

size_t Stream::write(uint8_t const* buf, size_t len) {
  size_t written {0};
  for (size_t i {0}; i < len; ++i) {
    written += write(buf[i]);
  }
  return written;
}

size_t Stream::readBytes(char* buf, size_t len) {
  size_t read_count {0};
  for (; read_count < len; ++read_count) {
    int c {read()};
    if (c < 0) {
      break;
    }
    buf[read_count] = static_cast<char>(c);
  }
  return read_count;
}

void SerialStream::begin(uint32_t baud) {
  serial_init(baud);
}

size_t SerialStream::write(uint8_t byte) {
  return serial_write_byte(byte);
}

size_t SerialStream::write(uint8_t const* buf, size_t len) {
  return serial_write(buf, len);
}

int SerialStream::available() {
  return serial_available();
}

int SerialStream::read() {
  return static_cast<int>(serial_read_byte());
}

SerialStream Serial {};
#endif
