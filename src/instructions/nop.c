#include "cpu.h"
#include "instructions.h"

void nop(cpu_t *, uint8_t, uint8_t *, uint8_t *) { 
   // Just debug
   printf("NOP\n");
   while (true) {}
   
   return;
}