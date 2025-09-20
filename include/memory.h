#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>
#include "cpu.h"

// General purpose registers R0-R7
uint8_t iram_read_register(cpu_t *cpu, iram_reg_t register);
void iram_write_register(cpu_t *cpu, iram_reg_t register, uint8_t value);

// Special function registers 0x80-0xFF
uint8_t sfr_read_register(cpu_t *cpu, sfr_reg_t register);
void sfr_write_register(cpu_t *cpu, sfr_reg_t register, uint8_t value);

// External memory
uint8_t xram_read(uint8_t *memory, uint16_t address);
void xram_write(uint8_t *memory, uint16_t address, uint8_t value);

#endif /* ! __MEMORY_H__ */