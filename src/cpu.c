#include <stdint.h>

#include "cpu.h"
#include "memory.h"

/*
 * Since all fields are already set to 0
 * on initalization, we only initalize non-zero values
 */
void cpu_reset(struct cpu_state* cpu) {
    sfr_write_register(cpu, REGISTER_SP, 0x07);

    sfr_write_register(cpu, REGISTER_P0, 0xFF);
    sfr_write_register(cpu, REGISTER_P1, 0xFF);
    sfr_write_register(cpu, REGISTER_P2, 0xFF);
    sfr_write_register(cpu, REGISTER_P3, 0xFF);
}

void cpu_execute_program(struct cpu_state* cpu, uint8_t* memory) {
    return;
}