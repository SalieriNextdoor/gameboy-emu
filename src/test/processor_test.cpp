/**
 * @file processor_test.cpp
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Runs tests for the processor.
 */
#include "../clock.h"
#include "../memory.h"
#include "../parser.h"
#include "../processor.h"

Memory m{""};
Processor pr{&m};
parser::Parser pa;

int cycle_count = 0;

parser::Operation last;
void fetch() {
  byte read_byte = m.read(pr.PC++);
  last = pa.parse(read_byte);
}

void run_op() {
  execute_cycle(fetch);
  pr.process(last);
}

int processor_test() {
  int all_passed = 0;

  m.write(pr.PC, 0x03); // INC BC
  run_op();
  if (pr.BC == 1 && cycle_count == last.tcycles / 4 + 1 && pr.PC == 1)
    std::cout << "PASS 0x03 test" << std::endl;
  else {
    std::cout << "FAIL 0x03 test" << std::endl;
    all_passed = 1;
  }
  cycle_count = 0;

  pr.SP.lo = 10;
  pr.SP.hi = 16;
  m.write(pr.PC, 0x08); // LD (u16),SP
  m.write(pr.PC + 1, 0xA8);
  m.write(pr.PC + 2, 0xC0);
  run_op();
  if (m.read(0xC0A8) == pr.SP.lo && m.read(0xC0A9) == pr.SP.hi &&
      cycle_count == last.tcycles / 4 + 1 && pr.PC == 4)
    std::cout << "PASS 0x08 test" << std::endl;
  else {
    std::cout << "FAIL 0x08 test" << std::endl;
    all_passed = 1;
  }
  cycle_count = 0;

  return all_passed;
}
