/**
 * @file fetcher.h
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Declares the classes and methods related to fetching.
 */
#ifndef GAMEBOY_FETCHER_H
#define GAMEBOY_FETCHER_H
#include "def.h"
#include <cstdio>

class Fetcher {
  byte *ROM;

public:
  Fetcher(byte *ROM);
  byte read[3];
  void fetch(u16 pos, byte n);
};

#endif
