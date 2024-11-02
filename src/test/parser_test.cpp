/**
 * @file parser_test.cpp
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Runs tests for the parser.
 */
#include "../parser.h"
#include <iostream>
using namespace parser;

int parser_test() {
  int all_passed = 0;
  Parser p;
  Operation t;

  t = p.parse(0x10);
  if (t.inst == Instruction::STOP && t.length == 0 && t.tcycles == 0)
    std::cout << "PASS 0x10 test" << std::endl;
  else {
    std::cout << "FAIL 0x10 test" << std::endl;
    all_passed = 1;
  }

  t = p.parse(0x03); // INC BC
  if (t.inst == Instruction::INC_RP && t.length == 0 && t.tcycles == 4 &&
      t.u16operation.reg1_1 == tablerp::BC)
    std::cout << "PASS 0x03 test" << std::endl;
  else {
    std::cout << "FAIL 0x03 test" << std::endl;
    all_passed = 1;
  }

  t = p.parse(0x13); // INC DE
  if (t.inst == Instruction::INC_RP && t.length == 0 && t.tcycles == 4 &&
      t.u16operation.reg1_1 == tablerp::DE)
    std::cout << "PASS 0x13 test" << std::endl;
  else {
    std::cout << "FAIL 0x13 test" << std::endl;
    all_passed = 1;
  }

  t = p.parse(0x1B); // DEC DE
  if (t.inst == Instruction::DEC_RP && t.length == 0 && t.tcycles == 4 &&
      t.u16operation.reg1_1 == tablerp::DE)
    std::cout << "PASS 0x1B test" << std::endl;
  else {
    std::cout << "FAIL 0x1B test" << std::endl;
    all_passed = 1;
  }

  t = p.parse(0xCB); // CB Prefix
  if (t.inst == Instruction::CB_PREFIX && t.length == 1 && t.tcycles == 4)
    std::cout << "PASS 0xCB Prefix test" << std::endl;
  else {
    std::cout << "FAIL 0xCB Prefix test" << std::endl;
    all_passed = 1;
  }
  t = p.parseCB(0x74); // CB: BIT 6,H
  if (t.inst == Instruction::BIT && t.length == 0 && t.tcycles == 4 &&
      t.n == 6 && t.cboperation.reg == tabler::H)
    std::cout << "PASS 0xCB 0x74 test" << std::endl;
  else {
    std::cout << "FAIL 0xCB 0x74 test" << std::endl;
    all_passed = 1;
  }
  t = p.parseCB(0x38); // CB: SRL B
  if (t.inst == Instruction::ROT && t.length == 0 && t.tcycles == 4 &&
      t.cboperation.rotop == tablerot::SRL && t.cboperation.reg == tabler::B)
    std::cout << "PASS 0xCB 0x74 test" << std::endl;
  else {
    std::cout << "FAIL 0xCB 0x74 test" << std::endl;
    all_passed = 1;
  }

  t = p.parse(0x4D); // LD C,L
  if (t.inst == Instruction::LD_R_R && t.length == 0 && t.tcycles == 0 &&
      t.u8operation.reg1 == tabler::C && t.u8operation.reg2 == tabler::L)
    std::cout << "PASS 0x4D test" << std::endl;
  else {
    std::cout << "FAIL 0x4D test" << std::endl;
    all_passed = 1;
  }
  t = p.parse(0x5E); // LD E,(HL)
  if (t.inst == Instruction::LD_R_R && t.length == 0 && t.tcycles == 4 &&
      t.u8operation.reg1 == tabler::E && t.u8operation.reg2 == tabler::HLd)
    std::cout << "PASS 0x5E test" << std::endl;
  else {
    std::cout << "FAIL 0x5E test" << std::endl;
    all_passed = 1;
  }
  t = p.parse(0x69); // LD L,C
  if (t.inst == Instruction::LD_R_R && t.length == 0 && t.tcycles == 0 &&
      t.u8operation.reg1 == tabler::L && t.u8operation.reg2 == tabler::C)
    std::cout << "PASS 0x69 test" << std::endl;
  else {
    std::cout << "FAIL 0x69 test" << std::endl;
    all_passed = 1;
  }
  t = p.parse(0x73); // LD (HL),E
  if (t.inst == Instruction::LD_R_R && t.length == 0 && t.tcycles == 4 &&
      t.u8operation.reg1 == tabler::HLd && t.u8operation.reg2 == tabler::E)
    std::cout << "PASS 0x73 test" << std::endl;
  else {
    std::cout << "FAIL 0x73 test" << std::endl;
    all_passed = 1;
  }

  t = p.parse(0xFF); // RST 38h
  if (t.inst == Instruction::RST && t.length == 0 && t.tcycles == 12 &&
      t.n == 0x38)
    std::cout << "PASS 0xFF test" << std::endl;
  else {
    std::cout << "FAIL 0xFF test" << std::endl;
    all_passed = 1;
  }

  return all_passed;
}
