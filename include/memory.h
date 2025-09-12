#ifndef __MEMORY_H__
#define __MEMORY_H__

#include <stdint.h>

void memory_read(uint8_t* memory, uint16_t address, uint8_t size);
void memory_write(uint8_t* memory, uint16_t address, uint8_t value, uint8_t size);

#endif /* ! __MEMORY_H__ */