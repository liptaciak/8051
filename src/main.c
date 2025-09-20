#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cpu.h"
#include "memory.h"

#define MEMORY_SIZE 0x10000
static uint8_t xram[MEMORY_SIZE];

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <program>\n", argv[0]);
        return EXIT_FAILURE;
    }

    FILE* program = fopen(argv[1], "rb");
    if (!program) {
        perror("Failed to open file");
        return EXIT_FAILURE;
    }

    fseek(program, 0, SEEK_END);
    long filesize = ftell(program);
    rewind(program);

    if (filesize > MEMORY_SIZE) {
        fprintf(stderr, "Program too large to fit in memory (size: %ld bytes)\n", filesize);
        fclose(program);
        return EXIT_FAILURE;
    }

    size_t read = fread(xram, 1, filesize, program);
    if (read != filesize) {
        fprintf(stderr, "Failed to read entire file (read %zu bytes)\n", read);
        fclose(program);
        return EXIT_FAILURE;
    }
    fclose(program);

    cpu_t cpu = {0};
    cpu_reset(&cpu);
    
    return cpu_execute_program(&cpu, xram);
}