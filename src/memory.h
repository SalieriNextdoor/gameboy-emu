/**
 * @file memory.h
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Defines the memory-related methods.
 */
#ifndef GAMEBOY_MEMORY_H
#define GAMEBOY_MEMORY_H
#include "def.h"
#include <cstdio>

class Memory {
  byte ROM[0x8000];
  byte VRAM[0x2000];
  byte ERAM[0x2000];
  byte WRAM[0x2000];
  byte OAM[0xA0];
  byte IOREG[0x80];
  byte HRAM[0x7F];
  byte IEREG = 0;
  byte PPUmode = 1;

public:
  Memory(const char *filepath);
  byte *getIOReg(u16 addr);
  u8 read(u16 loc);
  void write(u16 loc, u8 val);
};

#endif
