#include "cpu.h"
#include "memory.h"

#include "instructions.h"

void mova(cpu_t *cpu, uint8_t operand, uint8_t *) {
    // TODO: Update flags
    sfr_write_register(cpu, REGISTER_ACC, operand);
}