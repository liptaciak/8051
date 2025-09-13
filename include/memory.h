#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>
#include "cpu.h"

// General purpose registers R0-R7 in internal memory
uint8_t iram_read_register(struct cpu_state* cpu, enum iram_register register);
void iram_write_register(struct cpu_state* cpu, enum iram_register register, uint8_t value);

// Bit registers 0x00-0x7F in internal memory
uint8_t iram_read_bit(struct cpu_state* cpu, uint8_t bit_address);
void iram_write_bit(struct cpu_state* cpu, uint8_t bit_address, bool value);

// External memory
uint8_t memory_read(uint8_t* memory, uint16_t address);
void memory_write(uint8_t* memory, uint16_t address, uint8_t value);

#endif /* ! __MEMORY_H__ */