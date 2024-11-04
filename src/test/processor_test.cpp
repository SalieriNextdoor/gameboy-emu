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
  int myPC = 0;

  m.write(myPC++, 0x00); // NOP
  run_op();
  if (cycle_count == last.tcycles / 4 + 1 && pr.PC == myPC)
    std::cout << "PASS 0x00 test" << std::endl;
  else {
    std::cout << "FAIL 0x00 test" << std::endl;
    all_passed = 1;
  }
  cycle_count = 0;


  m.write(myPC++, 0x03); // INC BC
  run_op();
  if (pr.BC == 1 && cycle_count == last.tcycles / 4 + 1 && pr.PC == myPC)
    std::cout << "PASS 0x03 test" << std::endl;
  else {
    std::cout << "FAIL 0x03 test" << std::endl;
    all_passed = 1;
  }
  cycle_count = 0;


  pr.SP.lo = 10;
  pr.SP.hi = 16;
  m.write(myPC++, 0x08); // LD (u16),SP
  m.write(myPC++, 0xA8);
  m.write(myPC++, 0xC0);
  run_op();
  if (m.read(0xC0A8) == pr.SP.lo && m.read(0xC0A9) == pr.SP.hi &&
      cycle_count == last.tcycles / 4 + 1 && pr.PC == myPC)
    std::cout << "PASS 0x08 test" << std::endl;
  else {
    std::cout << "FAIL 0x08 test" << std::endl;
    all_passed = 1;
  }
  cycle_count = 0;


  m.write(myPC++, 0x18); // JR u8
  m.write(myPC++, 4);
  myPC += 4;
  run_op();
  if (cycle_count == last.tcycles / 4 + 1 && pr.PC == myPC)
    std::cout << "PASS 0x18 test1" << std::endl;
  else {
    std::cout << "FAIL 0x18 test1" << std::endl;
    all_passed = 1;
  }
  cycle_count = 0;
  m.write(myPC++, 0x18); // JR u8
  m.write(myPC++, -6);
  myPC -= 6;
  run_op();
  if (cycle_count == last.tcycles / 4 + 1 && pr.PC == myPC)
    std::cout << "PASS 0x18 test2" << std::endl;
  else {
    std::cout << "FAIL 0x18 test2" << std::endl;
    all_passed = 1;
  }
  cycle_count = 0;
  myPC = pr.PC = 0x0101;
  m.write(myPC++, 0x18); // JR u8
  m.write(myPC++, -4);
  myPC -= 4;
  run_op(); // 0x0103 - 4 
  if (cycle_count == last.tcycles / 4 + 1 && pr.PC == myPC)
    std::cout << "PASS 0x18 test3" << std::endl;
  else {
    std::cout << "FAIL 0x18 test3" << std::endl;
    all_passed = 1;
  }
  cycle_count = 0;
  cycle_count = 0;
  myPC = pr.PC = 0x00FD;
  m.write(myPC++, 0x18); // JR u8
  m.write(myPC++, 1);
  myPC += 1;
  run_op(); // 0x00FF + 1
  if (cycle_count == last.tcycles / 4 + 1 && pr.PC == myPC)
    std::cout << "PASS 0x18 test4" << std::endl;
  else {
    std::cout << "FAIL 0x18 test4" << std::endl;
    all_passed = 1;
  }
  cycle_count = 0;

  
  myPC = pr.PC = 0;
  m.write(myPC++, 0x20); // JR NZ,u8
  m.write(myPC++, 5);
  myPC += 5;
  run_op(); // cond = true
  // we add 2 because we store the least possible amount of cycles in last.tcycles
  if (cycle_count == last.tcycles / 4 + 2 && pr.PC == myPC)
    std::cout << "PASS 0x20 test1" << std::endl;
  else {
    std::cout << "FAIL 0x20 test1" << std::endl;
    all_passed = 1;
  }
  cycle_count = 0;
  m.write(myPC++, 0x28); // JR Z,u8 ()
  m.write(myPC++, 5);
  run_op(); // cond = false
  if (cycle_count == last.tcycles / 4 + 1 && pr.PC == myPC)
    std::cout << "PASS 0x20 test2" << std::endl;
  else {
    std::cout << "FAIL 0x20 test2" << std::endl;
    all_passed = 1;
  }
  cycle_count = 0;


  m.write(myPC++, 0x11); // LD DE,u16
  m.write(myPC++, 0xA8);
  m.write(myPC++, 0xC0);
  run_op(); // DE = 0xC0A8
  if (pr.DE == 0xC0A8 && cycle_count == last.tcycles / 4 + 1 && pr.PC == myPC)
    std::cout << "PASS 0x11 test" << std::endl;
  else {
    std::cout << "FAIL 0x11 test" << std::endl;
    all_passed = 1;
  }
  cycle_count = 0;


  return all_passed;
}
