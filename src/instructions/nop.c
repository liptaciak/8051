#include "cpu.h"
#include "instructions.h"

void nop(cpu_t *, instruction_t, uint8_t *) { 
   printf("NOP\n");

   // Just debug
   while (true) { }
}