#ifndef __INSTRUCTIONS_H__
#define __INSTRUCTIONS_H__

#include "cpu.h"

#define INSTRUCTION_COUNT 0x100

enum addresing_mode {
	MODE_IMMIDIATE
	// TODO: ...
}

struct instruction {
	void (*implementation)(struct cpu*, uint8_t*, uint8_t*);
	enum addressing_mode addressing_mode;
};

extern struct instruction instructions[INSTRUCTION_COUNT];

#endif /* ! __INSTRUCTIONS_H__ */