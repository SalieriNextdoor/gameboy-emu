/**
 * @file processor.h
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Defines the CPU-related methods.
 */
#ifndef GAMEBOY_PROCESSOR_H
#define GAMEBOY_PROCESSOR_H
#include "parser.h"
#include "registers.h"
#include <unistd.h>

class Processor {
#ifndef GAMEBOY_TEST_DEBUG
  u16Reg AF, BC, DE, HL, SP;
  u16Reg PC;
  u16Reg *tablerp[4] = {&BC, &DE, &HL, &SP};
  // u16Reg* tablerp[4]  = {&BC, &DE, &HL, &SP};
  // u16Reg* tablerp2[4] = {&BC, &DE, &HL, &AF};
#endif

public:
#ifdef GAMEBOY_TEST_DEBUG
  u16Reg AF, BC, DE, HL, SP;
  u16Reg PC;
  u16Reg *tablerp[4] = {&BC, &DE, &HL, &SP};
  // u16Reg* tablerp[4]  = {&BC, &DE, &HL, &SP};
  // u16Reg* tablerp2[4] = {&BC, &DE, &HL, &AF};
#endif

  void process(parser::Operation op, byte *read);
};

#endif
