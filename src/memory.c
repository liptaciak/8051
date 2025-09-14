#include <stdint.h>
#include <stdbool.h>

#include "cpu.h"
#include "memory.h"

uint8_t iram_read_register(struct cpu* cpu, enum iram_reg reg) {
    uint8_t psw = sfr_read_register(cpu, REGISTER_PSW);
    uint8_t active_bank = (psw >> 3) & 3;

    return cpu->ram[reg + 8 * active_bank];
}

void iram_write_register(struct cpu* cpu, enum iram_reg reg, uint8_t value) {
    uint8_t psw = sfr_read_register(cpu, REGISTER_PSW);
    uint8_t active_bank = (psw >> 3) & 3;

    cpu->ram[reg + 8 * active_bank] = value;
}

// TODO: IRAM bit registers

uint8_t sfr_read_register(struct cpu* cpu, enum sfr_reg reg) {
    if (reg < 0x80) return 0;
    return cpu->sfr[reg - 0x80];
}

void sfr_write_register(struct cpu* cpu, enum sfr_reg reg, uint8_t value) {
    if (reg < 0x80) return;
    cpu->sfr[reg - 0x80] = value;
}

// TODO: SFR bit registers

uint8_t xram_read(uint8_t* xram, uint16_t address) {
    return xram[address];
}

void xram_write(uint8_t* xram, uint16_t address, uint8_t value) {
    xram[address] = value;
}