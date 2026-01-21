#pragma once

#include "stream.h"
#include "interface.tcc"

// I/O plugins.
#if defined(ARDUINO)
#include "plugins/half_duplex/stream.h"
#endif
