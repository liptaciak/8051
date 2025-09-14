#include "instructions.h"

struct instruction instructions[INSTRUCTION_COUNT] = {
    [0x00] = {nop, MODE_IMMIDIATE} // Just an example
};