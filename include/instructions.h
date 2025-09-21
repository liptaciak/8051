#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

#include <stdint.h>

#include "cpu.h"

typedef enum {
	ADDRESSING_IMMEDIATE,         // Operand value directly in instruction
	ADDRESSING_REGISTER,          // Operand value is stored in a register
	ADDRESSING_DIRECT,            // Operand value is stored in memory
	ADDRESSING_REGISTER_INDIRECT, // Operand value is stored in memory pointed by a register
	ADDRESSING_INDEXED,           // Operand value is stored in ROM
	ADDRESSING_IMPLICIT           // Operand is implied by the instruction
} addressing_mode_t;

#include "instructions/nop.h"
#include "instructions/mov.h"

#define INSTRUCTION_COUNT 0x100

typedef struct {
	// Opcode and addressing mode might not be needed
	void (*implementation)(cpu_t *, uint8_t, uint8_t *);
	addressing_mode_t addressing_mode;
} instruction_t;

extern instruction_t instructions[INSTRUCTION_COUNT];

#endif /* ! __INSTRUCTIONS_H__ */