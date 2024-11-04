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
#include "util.h"
#include <functional>
#include <iostream>

Processor::Processor(Memory *m) : memory{m}, IF{m->getIOReg(0xFF0F)} {}

bool Processor::check_condition(parser::tablecc cond) {
  switch (cond) {
  case parser::tablecc::NZ:
    return !util::read_bit(AF, 7);
  case parser::tablecc::Z:
    return util::read_bit(AF, 7);
  case parser::tablecc::NC:
    return !util::read_bit(AF, 4);
  case parser::tablecc::C:
    return util::read_bit(AF, 4);
  }
  return false; // will never run
}

void Processor::process(parser::Operation op) {
  switch (op.inst) {
  case parser::Instruction::NOP: {
    break;
  }
  case parser::Instruction::INC_RP: {
    int idx = static_cast<int>(op.u16operation.reg1_1);
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
  case parser::Instruction::JR_D: {
    u8 val;
    execute_cycle([this](u8 &val) { val = memory->read(PC++); }, val);
    execute_cycle([this](u8 &val) { PC += (char)val; }, val);
    break;
  }
  case parser::Instruction::JR_CC: {
    u8 val;
    execute_cycle([this](u8 &val) { val = memory->read(PC++); }, val);
    if (check_condition(op.cond))
      execute_cycle([this](u8 &val) { PC += (char)val; }, val);
    break;
  }
  case parser::Instruction::LD_RP: {
    u8 lo = 0, hi = 0;
    execute_cycle([this](u8 &lo) { lo = memory->read(PC++); }, lo);
    execute_cycle([this](u8 &hi) { hi = memory->read(PC++); }, hi);
    int idx = static_cast<int>(op.u16operation.reg1_1);
    u16Reg *rp = tablerp[idx];
    *rp = u16Reg{hi, lo};
    break;
  }
  }
}
