/**
 * @file processor_test.cpp
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Runs tests for the processor.
 */
#include "../processor.h"
#include "../parser.h"
#include "../fetcher.h"
#include "../clock.h"

int cycle_count = 0;

int processor_test() {
  int all_passed = 0;
  byte ROM[0x8000];
  Processor pr;
  Fetcher fetcher{ROM};
  parser::Parser pa;
  parser::Operation t;

  ROM[0] = 0x03; // INC BC
  execute_cycle([&fetcher](int a, int b){fetcher.fetch(a, b);}, 0, 0);
  t = pa.parse(fetcher.read[0]);
  pr.process(t, fetcher.read);
  if (pr.BC == 1 && cycle_count == t.tcycles / 4 + 1)
    std::cout << "PASS 0x03 test" << std::endl;
  else {
    std::cout << "FAIL 0x03 test" << std::endl;
    all_passed = 1;
  }

  return all_passed;
}
