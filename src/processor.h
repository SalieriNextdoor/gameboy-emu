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
#include "memory.h"
#include "parser.h"
#include "registers.h"

class Processor {

  Memory *memory;
#ifndef GAMEBOY_TEST_DEBUG
  u16Reg AF, BC, DE, HL, SP;
  u16Reg PC;
  u16Reg *tablerp[4] = {&BC, &DE, &HL, &SP};
  // u16Reg* tablerp[4]  = {&BC, &DE, &HL, &SP};
  // u16Reg* tablerp2[4] = {&BC, &DE, &HL, &AF};
#endif

bool check_condition(parser::tablecc cond);

public:
#ifdef GAMEBOY_TEST_DEBUG
  u16Reg AF, BC, DE, HL, SP;
  u16Reg PC;
  u16Reg *tablerp[4] = {&BC, &DE, &HL, &SP};
  byte IME = 1;
  byte *IF;
  // u16Reg* tablerp[4]  = {&BC, &DE, &HL, &SP};
  // u16Reg* tablerp2[4] = {&BC, &DE, &HL, &AF};
#endif
  Processor(Memory *m);

  void process(parser::Operation op);
};

#endif
