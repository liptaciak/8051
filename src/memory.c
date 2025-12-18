#include <stdint.h>
#include <stdbool.h>

#include "cpu.h"
#include "memory.h"

uint8_t iram_read(cpu_t *cpu, uint8_t address) {
    if (address >= 0x80) return 0;
    return cpu->ram[address];
}

void iram_write(cpu_t *cpu, uint8_t address, uint8_t value) {
    if (address >= 0x80) return;
    cpu->ram[address] = value;
}

uint8_t iram_read_register(cpu_t *cpu, iram_reg_t reg) {
    uint8_t psw = sfr_read_register(cpu, REGISTER_PSW);
    uint8_t active_bank = (psw >> 3) & 0b11;

    return cpu->ram[reg + 8 * active_bank];
}

void iram_write_register(cpu_t *cpu, iram_reg_t reg, uint8_t value) {
    uint8_t psw = sfr_read_register(cpu, REGISTER_PSW);
    uint8_t active_bank = (psw >> 3) & 0b11;

    cpu->ram[reg + 8 * active_bank] = value;
}

// TODO: IRAM bit registers

uint8_t sfr_read_register(cpu_t *cpu, sfr_reg_t reg) {
    if (reg < 0x80 || reg > 0xFF) return 0;
    return cpu->sfr[reg - 0x80];
}

void sfr_write_register(cpu_t *cpu, sfr_reg_t reg, uint8_t value) {
    if (reg < 0x80 || reg > 0xFF) return;
    cpu->sfr[reg - 0x80] = value;
}

// TODO: SFR bit registers

uint8_t memory_read(cpu_t *cpu, uint8_t address) {
    if (address < 0x80) {
        return iram_read(cpu, address);
    } else if (address >= 0x80 && address <= 0xFF) {
        return sfr_read_register(cpu, address);
    }

    return 0;
}

uint8_t xram_read(uint8_t *xram, uint16_t address) {
    return xram[address];
}

void xram_write(uint8_t *xram, uint16_t address, uint8_t value) {
    xram[address] = value;
}