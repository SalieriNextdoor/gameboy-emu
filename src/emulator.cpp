/**
 * @file emulator.cpp
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Implements the main emulator methods.
 */
#include "emulator.h"
#include "clock.h"
#include <functional>
#include <thread>

Emulator::Emulator(const char* filepath) : memory{filepath}, processor{&memory} {}

parser::Operation last;
void Emulator::fetch() {
  byte read_byte = memory.read(processor.PC++);
  last = parser.parse(read_byte);
}

void Emulator::run() {
  execute_cycle([this]() { fetch(); });
  processor.process(last);
}
