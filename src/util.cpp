#include "util.h"

namespace util {
byte read_bit(byte val, byte nbit) { return (val & (1 << nbit)) ? 1 : 0; }
byte set_bit(byte val, byte nbit) { return val | (1 << nbit); }
byte unset_bit(byte val, byte nbit) { return val & ~(1 << nbit); }
}; // namespace util
