/**
 * @file parser.cpp
 * @copyright
 * Copyright 2024 Rafael Spinassé
 * Licensed under MIT license
 *
 * @brief Implements the classes and methods related to parsing.
 */
#include "parser.h"
using namespace parser;

Operation Parser::parse(byte opcode) {
  byte x = (opcode & 0700) >> 6;
  byte y = (opcode & 070) >> 3;
  byte z = opcode & 07;
  switch (x) {
  case 0:
    switch (z) {
    case 0:
      switch (y) {
      case 0:
        return {.inst = Instruction::NOP, .length = 0, .tcycles = 0};
      case 1:
        return {.inst = Instruction::LD_SP,
                .length = 2,
                .tcycles = 16,
                .u16operation = {.reg1_1 = tablerp::SP}};
      case 2:
        return {.inst = Instruction::STOP, .length = 0, .tcycles = 0};
      case 3:
        return {.inst = Instruction::JR_D, .length = 1, .tcycles = 8};
      case 4 ... 7:
        return {.inst = Instruction::JR_CC,
                .length = 1,
                .tcycles = 4,
                .cond = static_cast<tablecc>(y - 4)};
      }
    case 1:
      if (y % 2 == 0)
        return {.inst = Instruction::LD_RP,
                .length = 2,
                .tcycles = 8,
                .u16operation = {.reg1_1 = static_cast<tablerp>(y >> 1)}};
      else
        return {.inst = Instruction::ADD_HL,
                .length = 0,
                .tcycles = 4,
                .u16operation = {.reg1_1 = tablerp::HL,
                                 .reg2_1 = static_cast<tablerp>(y >> 1)}};
    case 2:
      if (y % 2 == 0) {
        switch (y >> 1) {
        case 0:
          return {.inst = Instruction::LD_BC,
                  .length = 0,
                  .tcycles = 4,
                  .u16operation = {.reg1_1 = tablerp::BC, .regA2 = tabler::A}};
        case 1:
          return {.inst = Instruction::LD_DE,
                  .length = 0,
                  .tcycles = 4,
                  .u16operation = {.reg1_1 = tablerp::DE, .regA2 = tabler::A}};
        case 2:
          return {.inst = Instruction::LD_HLP,
                  .length = 0,
                  .tcycles = 4,
                  .u16operation = {.reg1_1 = tablerp::HL, .regA2 = tabler::A}};
        case 3:
          return {.inst = Instruction::LD_HLM,
                  .length = 0,
                  .tcycles = 4,
                  .u16operation = {.reg1_1 = tablerp::HL, .regA2 = tabler::A}};
        }
      } else {
        switch (y >> 1) {
        case 0:
          return {.inst = Instruction::LD_A_BC,
                  .length = 0,
                  .tcycles = 4,
                  .u16operation = {.regA1 = tabler::A, .reg2_1 = tablerp::BC}};
        case 1:
          return {.inst = Instruction::LD_A_DE,
                  .length = 0,
                  .tcycles = 4,
                  .u16operation = {.regA1 = tabler::A, .reg2_1 = tablerp::DE}};
        case 2:
          return {.inst = Instruction::LD_A_HLP,
                  .length = 0,
                  .tcycles = 4,
                  .u16operation = {.regA1 = tabler::A, .reg2_1 = tablerp::HL}};
        case 3:
          return {.inst = Instruction::LD_A_HLM,
                  .length = 0,
                  .tcycles = 4,
                  .u16operation = {.regA1 = tabler::A, .reg2_1 = tablerp::HL}};
        }
      }
    case 3:
      if (y % 2 == 0)
        return {.inst = Instruction::INC_RP,
                .length = 0,
                .tcycles = 4,
                .u16operation = {.reg1_1 = static_cast<tablerp>(y >> 1)}};
      else
        return {.inst = Instruction::DEC_RP,
                .length = 0,
                .tcycles = 4,
                .u16operation = {.reg1_1 = static_cast<tablerp>(y >> 1)}};
    case 4:
      return {.inst = Instruction::INC_R,
              .length = 0,
              .tcycles = 0,
              .u8operation = {.reg1 = static_cast<tabler>(y)}};
    case 5:
      return {.inst = Instruction::DEC_R,
              .length = 0,
              .tcycles = 0,
              .u8operation = {.reg1 = static_cast<tabler>(y)}};
    case 6:
      return {.inst = Instruction::LD_R_N,
              .length = 1,
              .tcycles = 4,
              .u8operation = {.reg1 = static_cast<tabler>(y)}};
    case 7:
      switch (y) {
      case 0:
        return {.inst = Instruction::RLCA, .length = 0, .tcycles = 0};
      case 1:
        return {.inst = Instruction::RRCA, .length = 0, .tcycles = 0};
      case 2:
        return {.inst = Instruction::RLA, .length = 0, .tcycles = 0};
      case 3:
        return {.inst = Instruction::RRA, .length = 0, .tcycles = 0};
      case 4:
        return {.inst = Instruction::DAA, .length = 0, .tcycles = 0};
      case 5:
        return {.inst = Instruction::CPL, .length = 0, .tcycles = 0};
      case 6:
        return {.inst = Instruction::SCF, .length = 0, .tcycles = 0};
      case 7:
        return {.inst = Instruction::CCF, .length = 0, .tcycles = 0};
      }
    }
  case 1:
    if (y == 6 && z == 6)
      return {.inst = Instruction::HALT, .length = 0, .tcycles = 0};
    else if (z == 6)
      return {
          .inst = Instruction::LD_R_R,
          .length = 0,
          .tcycles = 4,
          .u8operation = {.reg1 = static_cast<tabler>(y), .reg2 = tabler::HLd}};
    else if (y == 6)
      return {.inst = Instruction::LD_R_R,
              .length = 0,
              .tcycles = 4,
              .u8operation = {
                  .reg1 = tabler::HLd,
                  .reg2 = static_cast<tabler>(z),
              }};
    else
      return {.inst = Instruction::LD_R_R,
              .length = 0,
              .tcycles = 0,
              .u8operation = {.reg1 = static_cast<tabler>(y),
                              .reg2 = static_cast<tabler>(z)}};
  case 2:
    if (z != 6)
      return {.inst = Instruction::ALU_R,
              .length = 0,
              .tcycles = 0,
              .u8operation = {.aluop = static_cast<tablealu>(y),
                              .reg2 = static_cast<tabler>(z)}};
    else
      return {.inst = Instruction::ALU_R,
              .length = 0,
              .tcycles = 4,
              .u8operation = {.aluop = static_cast<tablealu>(y),
                              .reg2 = tabler::HLd}};
  case 3:
    switch (z) {
    case 0:
      switch (y) {
      case 0 ... 3:
        return {.inst = Instruction::RET_CC,
                .length = 0,
                .tcycles = 4,
                .cond = static_cast<tablecc>(y)};
      case 4:
        return {.inst = Instruction::LD_HEX_A,
                .length = 1,
                .tcycles = 8,
                .u8operation = {.reg2 = tabler::A}};
      case 5:
        return {.inst = Instruction::ADD_SP,
                .length = 1,
                .tcycles = 12,
                .u16operation = {.reg1_1 = tablerp::SP}};
      case 6:
        return {.inst = Instruction::LD_A_HEX,
                .length = 1,
                .tcycles = 8,
                .u8operation = {.reg1 = tabler::A}};
      case 7:
        return {.inst = Instruction::LD_HL_SP,
                .length = 1,
                .tcycles = 8,
                .u16operation = {.reg1_1 = tablerp::HL, .reg2_1 = tablerp::SP}};
      }
    case 1:
      if (y % 2 == 0)
        return {.inst = Instruction::POP,
                .length = 0,
                .tcycles = 8,
                .u16operation = {.reg1_2 = static_cast<tablerp2>(y >> 1)}};
      else {
        switch (y >> 1) {
        case 0:
          return {.inst = Instruction::RET, .length = 0, .tcycles = 12};
        case 1:
          return {.inst = Instruction::RETI, .length = 0, .tcycles = 12};
        case 2:
          return {.inst = Instruction::JP_HL,
                  .length = 0,
                  .tcycles = 0,
                  .u16operation = {.reg1_1 = tablerp::HL}};
        case 3:
          return {
              .inst = Instruction::LD_SP_HL,
              .length = 0,
              .tcycles = 4,
              .u16operation = {.reg1_1 = tablerp::SP, .reg2_1 = tablerp::HL}};
        }
      }
    case 2:
      switch (y) {
      case 0 ... 3:
        return {.inst = Instruction::JP_CC,
                .length = 2,
                .tcycles = 8,
                .cond = static_cast<tablecc>(y)};
      case 4:
        return {.inst = Instruction::LD_HEXC_A,
                .length = 0,
                .tcycles = 4,
                .u8operation{.reg1 = tabler::C, .reg2 = tabler::A}};
      case 5:
        return {.inst = Instruction::LD_N_A,
                .length = 2,
                .tcycles = 12,
                .u8operation = {.reg2 = tabler::A}};
      case 6:
        return {.inst = Instruction::LD_A_HEXC,
                .length = 0,
                .tcycles = 4,
                .u8operation{.reg1 = tabler::A, .reg2 = tabler::C}};
      case 7:
        return {.inst = Instruction::LD_A_N,
                .length = 2,
                .tcycles = 12,
                .u8operation{.reg1 = tabler::A}};
      }
    case 3:
      switch (y) {
      case 0:
        return {.inst = Instruction::JP, .length = 2, .tcycles = 12};
      case 1:
        return {.inst = Instruction::CB_PREFIX, .length = 1, .tcycles = 4};
      case 2 ... 5:
        return {.inst = Instruction::NOP, .length = 0, .tcycles = 0};
      case 6:
        return {.inst = Instruction::DI, .length = 0, .tcycles = 0};
      case 7:
        return {.inst = Instruction::EI, .length = 0, .tcycles = 0};
      }
    case 4:
      switch (y) {
      case 0 ... 3:
        return {.inst = Instruction::CALL_CC,
                .length = 2,
                .tcycles = 8,
                .cond = static_cast<tablecc>(y)};
      case 4 ... 7:
        return {.inst = Instruction::NOP, .length = 0, .tcycles = 0};
      }
    case 5:
      if (y % 2 == 0)
        return {.inst = Instruction::PUSH,
                .length = 0,
                .tcycles = 12,
                .u16operation = {.reg1_2 = static_cast<tablerp2>(y >> 1)}};
      else if ((y >> 1) == 0)
        return {.inst = Instruction::CALL, .length = 2, .tcycles = 20};
      else
        return {.inst = Instruction::NOP, .length = 0, .tcycles = 0};
    case 6:
      return {.inst = Instruction::ALU_N,
              .length = 1,
              .tcycles = 4,
              .u8operation = {.aluop = static_cast<tablealu>(y)}};
    case 7:
      y *= 8;
      return {.inst = Instruction::RST, .length = 0, .tcycles = 12, .n = y};
    }
  }
  return {.inst = Instruction::NOP, // not generally expected to be reached
          .length = 0,
          .tcycles = 0};
}

Operation Parser::parseCB(byte opcode) {
  byte x = (opcode & 0700) >> 6;
  byte y = (opcode & 070) >> 3;
  byte z = opcode & 07;
  switch (x) {
  case 0:
    return {.inst = Instruction::ROT,
            .length = 0,
            .tcycles = 4,
            .cboperation = {.rotop = static_cast<tablerot>(y),
                            .reg = static_cast<tabler>(z)}};
  case 1:
    return {.inst = Instruction::BIT,
            .length = 0,
            .tcycles = 4,
            .cboperation = {.n = y, .reg = static_cast<tabler>(z)}};
  case 2:
    return {.inst = Instruction::RES,
            .length = 0,
            .tcycles = 4,
            .cboperation = {.n = y, .reg = static_cast<tabler>(z)}};
  case 3:
    return {.inst = Instruction::SET,
            .length = 0,
            .tcycles = 4,
            .cboperation = {.n = y, .reg = static_cast<tabler>(z)}};
  }
  return {.inst = Instruction::NOP, // not generally expected to be reached
          .length = 0,
          .tcycles = 0};
}
