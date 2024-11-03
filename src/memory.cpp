/**
 * @file memory.cpp
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Implements the memory-related methods.
 */
#include "memory.h"
#include <stdexcept>

Memory::Memory(const char *filepath) {
  FILE *fp = fopen(filepath, "rb");
  if (fp != NULL) {
    fseek(fp, 0, SEEK_END);
    long sz = ftell(fp);
    rewind(fp);
    if (sz > 0x8000) {
      fclose(fp);
      throw std::length_error("File is too large");
    }
    fread(&ROM, sizeof(char), sz, fp);
    fclose(fp);
  }
}

byte *Memory::getIOReg(u16 addr) { return &IOREG[addr - 0xFF00]; }

u8 Memory::read(u16 loc) {
  switch (loc) {
  case 0 ... 0x7FFF:
    return ROM[loc];
  case 0x8000 ... 0x9FFF:
    return VRAM[loc - 0x8000];
  case 0xA000 ... 0xBFFF:
    return ERAM[loc - 0xA000];
  case 0xC000 ... 0xDFFF:
    return WRAM[loc - 0xC000];
  case 0xE000 ... 0xFDFF:
    return WRAM[loc - 0xE000];
  case 0xFE00 ... 0xFE9F:
    if (PPUmode == 0 || PPUmode == 1)
      return OAM[loc - 0xFE00];
    else
      return 0xFF;
  case 0xFEA0 ... 0xFEFF:
    if (PPUmode == 0 || PPUmode == 1) {
      u8 temp = loc & 0xF0;
      return temp | (temp >> 4);
    } else
      return 0xFF;
  case 0xFF00 ... 0xFF7F:
    return IOREG[loc - 0xFF00];
  case 0xFF80 ... 0xFFFE:
    return HRAM[loc - 0xFF80];
  case 0xFFFF:
    return IEREG;
  default:
    return 0xFF;
  }
}

void Memory::write(u16 loc, u8 val) {
  switch (loc) {
#ifdef GAMEBOY_TEST_DEBUG
  case 0x0000 ... 0x7FFF:
    ROM[loc] = val;
    break;
#endif
  case 0x8000 ... 0x9FFF:
    VRAM[loc - 0x8000] = val;
    break;
  case 0xA000 ... 0xBFFF:
    ERAM[loc - 0xA000] = val;
    break;
  case 0xC000 ... 0xDFFF:
    WRAM[loc - 0xC000] = val;
    break;
  case 0xE000 ... 0xFDFF:
    WRAM[loc - 0xE000] = val;
    break;
  case 0xFE00 ... 0xFE9F:
    if (PPUmode == 0 || PPUmode == 1)
      OAM[loc - 0xFE00] = val;
    break;
  case 0xFF00 ... 0xFF7F:
    IOREG[loc - 0xFF00] = val;
    break;
  case 0xFF80 ... 0xFFFE:
    HRAM[loc - 0xFF80] = val;
    break;
  case 0xFFFF:
    IEREG = val;
    break;
  }
}
