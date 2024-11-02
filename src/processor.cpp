/**
 * @file processor.cpp
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Implements the CPU-related methods.
 */
#include "processor.h"
#include "clock.h"
#include "parser.h"
#include "registers.h"
#include <functional>

void Processor::process(parser::Operation op, byte *read) {
  int idx;
  switch (op.inst) {
  case parser::Instruction::NOP:
    execute_cycle([]() {});
  case parser::Instruction::INC_RP:
    idx = static_cast<int>(op.u16operation.reg1_1);
    execute_cycle([](u16Reg *rp) { (*rp)++; }, tablerp[idx]);
  }
}
