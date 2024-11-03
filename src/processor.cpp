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
#include <iostream>

Processor::Processor(Memory *m) : memory{m}, IF{m->getIOReg(0xFF0F)} {}

void Processor::process(parser::Operation op) {
  int idx;
  switch (op.inst) {
  case parser::Instruction::NOP: {
    execute_cycle([]() {});
    break;
  }
  case parser::Instruction::INC_RP: {
    idx = static_cast<int>(op.u16operation.reg1_1);
    execute_cycle([](u16Reg *rp) { (*rp)++; }, tablerp[idx]);
    break;
  }
  case parser::Instruction::LD_SP: {
    u8 lo = 0, hi = 0;
    execute_cycle([this](u8 &lo) { lo = memory->read(PC++); }, lo);
    execute_cycle([this](u8 &hi) { hi = memory->read(PC++); }, hi);
    u16 addr = (hi << 8) | lo;
    execute_cycle([this](u16 addr) { memory->write(addr, SP.lo); }, addr);
    execute_cycle([this](u16 addr) { memory->write(addr + 1, SP.hi); }, addr);
    break;
  }
  case parser::Instruction::STOP: {
    // todo for GBC
    // https://gbdev.io/pandocs/Reducing_Power_Consumption.html#using-the-stop-instruction
    break;
  }
  }
}
