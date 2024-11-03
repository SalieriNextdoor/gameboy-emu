/**
 * @file registers.h
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Defines the registers and associated functions.
 */
#ifndef GAMEBOY_REGISTERS_H
#define GAMEBOY_REGISTERS_H
#include "def.h"

struct u16Reg {
  byte hi, lo;

  operator int() const { return (hi << 8) | lo; }

  u16Reg& operator=(u16 val) {
    hi = (byte)(val >> 8);
    lo = (byte)val;
    return *this;
  }

  u16Reg operator++(int) {
    u16Reg temp{hi, lo};
    lo++;
    if (lo == 0)
      hi++;
    return temp;
  }
};

#endif
