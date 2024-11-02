/**
 * @file fetcher.cpp
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Implements the classes and methods related to fetching.
 */
#include "fetcher.h"
#include <stdexcept>

Fetcher::Fetcher(byte *ROM) : ROM{ROM} {}

void Fetcher::fetch(u16 pos, byte n) {
  if (pos >= 0 && pos <= 0x7FFF)
    read[n] = ROM[pos];
  else
    throw std::runtime_error("Couldn't access ROM position.");
}
