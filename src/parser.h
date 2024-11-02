/**
 * @file parser.h
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Declares the classes and methods related to parsing.
 */
#ifndef GAMEBOY_PARSER_H
#define GAMEBOY_PARSER_H

#include "def.h"

namespace parser {
enum class Instruction {
  // Unprefixed Opcodes
  NOP,
  LD_SP,
  STOP,
  JR_D,
  JR_CC,
  LD_RP,
  ADD_HL,
  LD_BC,
  LD_DE,
  LD_HLP,
  LD_HLM,
  LD_A_BC,
  LD_A_DE,
  LD_A_HLP,
  LD_A_HLM,
  INC_RP,
  DEC_RP,
  INC_R,
  DEC_R,
  LD_R_N,
  RLCA,
  RRCA,
  RLA,
  RRA,
  DAA,
  CPL,
  SCF,
  CCF,
  LD_R_R,
  HALT,
  ALU_R,
  RET_CC,
  LD_HEX_A,
  ADD_SP,
  LD_A_HEX,
  LD_HL_SP,
  POP,
  RET,
  RETI,
  JP_HL,
  LD_SP_HL,
  JP_CC,
  LD_HEXC_A,
  LD_N_A,
  LD_A_HEXC,
  LD_A_N,
  JP,
  CB_PREFIX,
  DI,
  EI,
  CALL_CC,
  PUSH,
  CALL,
  ALU_N,
  RST,

  // CB-Prefixed Opcodes
  ROT,
  BIT,
  RES,
  SET,
};

enum class tabler { B = 0, C, D, E, H, L, HLd, A };
enum class tablerp { BC = 0, DE, HL, SP };
enum class tablerp2 { BC = 0, DE, HL, AF };
enum class tablecc { NZ = 0, Z, NC, C };
enum class tablealu { ADD_A = 0, ADC_A, SUB, SBC_A, AND, XOR, OR, CP };
enum class tablerot { RLC = 0, RRC, RL, RR, SLA, SRA, SWAP, SRL };

struct u8op {
  union {
    tabler reg1;
    tablealu aluop;
  };
  union {
    tabler reg2;
  };
};

struct u16op {
  union {
    tablerp reg1_1;
    tablerp2 reg1_2;
    tabler regA1;
  };
  union {
    tablerp reg2_1;
    tablerp2 reg2_2;
    tabler regA2;
  };
};

struct cbop {
  union {
    u8 n;
    tablerot rotop;
  };
  tabler reg;
};

struct Operation {
  Instruction inst;
  byte length;  // n of bytes left to read (0-2)
  byte tcycles; // number of tcycles, excluding fetch, priority no branch
  union {
    u8op u8operation;
    u16op u16operation;
    tablecc cond;
    cbop cboperation;
    u8 n;
  };
};

class Parser {
public:
  Operation parse(byte opcode);
  Operation parseCB(byte opcode);
};
}; // namespace parser

#endif
