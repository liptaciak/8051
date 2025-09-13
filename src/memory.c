#include <stdint.h>

#include "cpu.h"
#include "memory.h"

uint8_t sfr_read_register(struct cpu_state* cpu, uint8_t sfr_address) {
    if (sfr_address < 0x80) return 0;
    return cpu->sfr[sfr_address - 0x80];
}

void sfr_write_register(struct cpu_state* cpu, uint8_t sfr_address, uint8_t value) {
    if (sfr_address < 0x80) return;
    cpu->sfr[sfr_address - 0x80] = value;
}

bool sfr_read_bit(struct cpu_state* cpu, uint8_t bit_address) {
    if (bit_address < 0x80) return false;
    if (bit_address > 0xFF) return false;

    uint8_t sfr_address = 0x80 + (bit_address / 8);
    uint8_t bit_position = bit_address % 8;

    if (sfr_address % 8 != 0) return false;
    return (cpu->sfr[sfr_address - 0x80] >> bit_position) & 1;
}

void sfr_write_bit(struct cpu_state* cpu, uint8_t bit_address, bool value) {
    if (bit_address < 0x80) return;
    if (bit_address > 0xFF) return;

    uint8_t sfr_address = 0x80 + (bit_address / 8);
    uint8_t bit_position = bit_address % 8;

    if (sfr_address % 8 != 0) return;
    if (value) {
        cpu->sfr[sfr_address - 0x80] |= (1 << bit_position);
    } else {
        cpu->sfr[sfr_address - 0x80] &= ~(1 << bit_position);
    }
}

uint8_t iram_read_register(struct cpu_state* cpu, enum iram_register register) {

}

uint8_t memory_read(uint8_t* memory, uint16_t address) {
    return memory[address];
}

void memory_write(uint8_t* memory, uint16_t address, uint8_t value) {
    memory[address] = value;
}