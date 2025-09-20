#include "instructions.h"

instruction_t instructions[INSTRUCTION_COUNT] = {
    [0x00] = {nop, ADDRESSING_IMPLICIT}
};