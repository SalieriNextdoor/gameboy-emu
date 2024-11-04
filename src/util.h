/**
 * @file util.h
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Defines general utility functions.
 */
#ifndef GAMEBOY_UTIL_H
#define GAMEBOY_UTIL_H
#include "def.h"

namespace util {
byte read_bit(byte val, byte nbit);
byte set_bit(byte val, byte nbit);
byte unset_bit(byte val, byte nbit);
}; // namespace util

#endif
