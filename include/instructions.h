#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

#include <stdint.h>

#include "cpu.h"

typedef enum {
	ADDRESSING_IMPLICIT,          // The instruction has no operands
	ADDRESSING_IMMEDIATE,         // Operand value is stored after the opcode
	ADDRESSING_DIRECT,            // Operand value is stored in memory
	ADDRESSING_REGISTER,          // Operand value is stored in a register
	ADDRESSING_REGISTER_INDIRECT, // Operand value is stored in memory pointed by a register
	ADDRESSING_BIT,               // Operand bit address is stored after the opcode
	ADDRESSING_INDEXED            // Operand value is stored in ROM
} addressing_mode_t;

#include "instructions/nop.h"
#include "instructions/mov.h"

#define INSTRUCTION_COUNT 0x100

typedef struct {
	// Opcode and addressing mode might not be needed
	void (*implementation)(cpu_t *cpu, uint8_t opcode, uint8_t *operands, uint8_t *xram);
	addressing_mode_t addressing_mode;
} instruction_t;

extern instruction_t instructions[INSTRUCTION_COUNT];

#endif /* ! __INSTRUCTIONS_H__ */