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

void Emulator::run() {
  /*  std::thread fetch_thread{[this]() {
      execute_cycle(
          [this](auto &&arg) { fetcher.fetch(std::forward<decltype(arg)>(arg));
    }, processor.PC);
    }};*/
  execute_cycle([this](u16 pos, byte n) { fetcher.fetch(pos, n); },
                processor.PC, 0);
  processor.PC++;
  parser::Operation op = parser.parse(fetcher.read[0]);
  for (int i = 1; i <= op.length; i++, processor.PC++)
    fetcher.fetch(processor.PC, i);
  processor.process(op, fetcher.read);
}
