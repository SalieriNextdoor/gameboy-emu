/**
 * @file clock.h
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Defines clock and timer-related methods.
 */ 
#ifndef GAMEBOY_CLOCK_H
#define GAMEBOY_CLOCK_H
#include <chrono>
#include <thread>
#include <iostream>

#ifdef GAMEBOY_TEST_DEBUG
extern int cycle_count;
#endif

// execute machine cycle
template<class F, class... Args>
void execute_cycle(F&& f, Args&&... args) {
  using namespace std::chrono;
  static const int cycle_time_ns = 1000; // 1MHz

#ifdef GAMEBOY_TEST_DEBUG
  cycle_count++;
#endif
  auto start = high_resolution_clock::now();

  // call f with args
  std::forward<F>(f)(std::forward<Args>(args)...);

  auto end = high_resolution_clock::now();
  duration<int, std::nano> elapsed = duration_cast<nanoseconds>(end - start);

  while (elapsed.count() < cycle_time_ns)
    elapsed = duration_cast<nanoseconds>(high_resolution_clock::now() - start);
}


#endif
