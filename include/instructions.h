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

#define INSTRUCTION_COUNT 0x100

typedef struct instruction_t instruction_t;
struct instruction_t {
	addressing_mode_t dst_addressing_mode;
	addressing_mode_t src_addressing_mode;
	void (*implementation)(cpu_t *cpu, instruction_t instruction, uint8_t *dst, uint8_t src);
	const char *format;
	uint8_t opcode;
};

#include "instructions/nop.h"
#include "instructions/mov.h"

extern instruction_t instructions[INSTRUCTION_COUNT];

#endif /* ! __INSTRUCTIONS_H__ */