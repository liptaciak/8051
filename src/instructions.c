#include "instructions.h"

/* 
 * R0 = 000
 * R1 = 001
 * R2 = 010
 * R3 = 011
 * R4 = 100
 * R5 = 101
 * R6 = 110
 * R7 = 111
 */

instruction_t instructions[INSTRUCTION_COUNT] = {
    // NOP
    [0x00] = {nop, ADDRESSING_IMPLICIT},
    // MOV A, #value
    [0x74] = {mova, ADDRESSING_IMMEDIATE},
    // MOV A, adr
    [0xE5] = {mova, ADDRESSING_DIRECT},
    // MOV A, @RI
    [0xE6] = {mova, ADDRESSING_REGISTER_INDIRECT},
    [0xE7] = {mova, ADDRESSING_REGISTER_INDIRECT},
    // MOV A, Rn
    [0xE8] = {mova, ADDRESSING_REGISTER},
    [0xE9] = {mova, ADDRESSING_REGISTER},
    [0xEA] = {mova, ADDRESSING_REGISTER},
    [0xEB] = {mova, ADDRESSING_REGISTER},
    [0xEC] = {mova, ADDRESSING_REGISTER},
    [0xED] = {mova, ADDRESSING_REGISTER},
    [0xEE] = {mova, ADDRESSING_REGISTER},
    [0xEF] = {mova, ADDRESSING_REGISTER}
};  