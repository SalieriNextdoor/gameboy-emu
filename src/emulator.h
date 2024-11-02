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
#include "fetcher.h"
#include "parser.h"
#include "processor.h"

class Emulator {
  byte ROM[0x8000];
  Fetcher fetcher{ROM};
  parser::Parser parser;
  Processor processor;

public:
  void run();
};
#endif
