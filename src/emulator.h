/**
 * @file emulator.h
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Defines the main emulator methods.
 */
#ifndef GAMEBOY_EMULATOR_H
#define GAMEBOY_EMULATOR_H
#include "clock.h"
#include "def.h"
#include "memory.h"
#include "parser.h"
#include "processor.h"

class Emulator {
  Memory memory;
  parser::Parser parser;
  Processor processor;

  Emulator(const char *filepath);

  void fetch();

public:
  void run();
};
#endif
