#include <stdio.h>
#include <stdint.h>

#include "cpu.h"
#include "memory.h"

#define MEMORY_SIZE 65536
static uint8_t memory[MEMORY_SIZE];

int main(int argc, char** argv) {
    struct cpu_state cpu;
    cpu.pc = 0;

    printf("Helou word\n");
    return 0;
}