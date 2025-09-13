#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>

uint8_t memory_read(uint8_t* memory, uint16_t address);
void memory_write(uint8_t* memory, uint16_t address, uint8_t value);

#endif /* ! __MEMORY_H__ */