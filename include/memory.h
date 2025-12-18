#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>
#include "cpu.h"

// Internal memory
uint8_t iram_read(cpu_t *cpu, uint8_t address);
void iram_write(cpu_t *cpu, uint8_t address, uint8_t value);

// Helper for general purpose registers R0-R7
uint8_t iram_read_register(cpu_t *cpu, iram_reg_t register);
void iram_write_register(cpu_t *cpu, iram_reg_t register, uint8_t value);

// Special function registers 0x80-0xFF
uint8_t sfr_read_register(cpu_t *cpu, sfr_reg_t register);
void sfr_write_register(cpu_t *cpu, sfr_reg_t register, uint8_t value);

// Helper function to read from any internal memory region
uint8_t memory_read(cpu_t *cpu, uint8_t address);

// External memory
uint8_t xram_read(uint8_t *memory, uint16_t address);
void xram_write(uint8_t *memory, uint16_t address, uint8_t value);

#endif /* ! __MEMORY_H__ */