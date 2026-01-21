#pragma once

#if defined(ARDUINO)
#include <Stream.h>
#else
#include <stddef.h>
#include <stdint.h>

class Stream {
public:
  virtual ~Stream() = default;

  virtual size_t write(uint8_t byte) = 0;
  virtual size_t write(uint8_t const* buf, size_t len);
  virtual int available() = 0;
  virtual int read() = 0;
  virtual size_t readBytes(char* buf, size_t len);
};

class SerialStream : public Stream {
public:
  void begin(uint32_t baud);

  size_t write(uint8_t byte) override;
  size_t write(uint8_t const* buf, size_t len) override;
  int available() override;
  int read() override;
};

extern SerialStream Serial;
#endif
