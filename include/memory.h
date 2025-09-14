#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>
#include "cpu.h"

// General purpose registers R0-R7 in internal memory
uint8_t iram_read_register(struct cpu_state* cpu, enum iram_reg register);
void iram_write_register(struct cpu_state* cpu, enum iram_reg register, uint8_t value);

// Special function registers 0x80-0xFF
uint8_t sfr_read_register(struct cpu_state* cpu, enum sfr_reg register);
void sfr_write_register(struct cpu_state* cpu, enum sfr_reg register, uint8_t value);

// External memory
uint8_t memory_read(uint8_t* memory, uint16_t address);
void memory_write(uint8_t* memory, uint16_t address, uint8_t value);

#endif /* ! __MEMORY_H__ */