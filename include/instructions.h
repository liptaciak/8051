#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

#include <stdint.h>

#include "cpu.h"

typedef enum {
	ADDRESSING_IMPLICIT,          // The instruction has no operands
	ADDRESSING_IMMEDIATE,         // Operand is the actual value
	ADDRESSING_DIRECT,            // Operand is the memory address (containing the value)
	ADDRESSING_REGISTER,          // Operand is the value of a register (R0-R7)
	ADDRESSING_REGISTER_INDIRECT, // Operand is the memory address pointed by a register (R0 or R1)
	ADDRESSING_BIT,               // Operand is the bit address
	ADDRESSING_INDEXED            // The instruction has no operands
} addressing_mode_t;

#include "instructions/nop.h"
#include "instructions/mov.h"

#define INSTRUCTION_COUNT 0x100

typedef struct {
	uint8_t opcode;
	addressing_mode_t addressing_mode;
	void (*implementation)(cpu_t *cpu, instruction_t instruction, uint8_t *operands);
} instruction_t;

extern instruction_t instructions[INSTRUCTION_COUNT];

#endif /* ! __INSTRUCTIONS_H__ */