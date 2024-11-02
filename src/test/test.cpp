/**
 * @file test.cpp
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Runs all tests.
 */ 
#include <iostream>
int parser_test();
int processor_test();

int main() {
  int all_passed = 0;

  std::cout << "=====PARSER TESTS=====" << std::endl;
  all_passed |= parser_test();
  std::cout << "=====PROCESSOR TESTS=====" << std::endl;
  all_passed |= processor_test();

  return all_passed;
}
