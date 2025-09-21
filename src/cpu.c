#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cpu.h"
#include "memory.h"
#include "instructions.h"

/*
 * Since all fields are already set to 0
 * on initalization, we only initalize non-zero values
 */
void cpu_reset(cpu_t *cpu) {
    sfr_write_register(cpu, REGISTER_SP, 0x07);

    sfr_write_register(cpu, REGISTER_P0, 0xFF);
    sfr_write_register(cpu, REGISTER_P1, 0xFF);
    sfr_write_register(cpu, REGISTER_P2, 0xFF);
    sfr_write_register(cpu, REGISTER_P3, 0xFF);
}

int cpu_execute_program(cpu_t *cpu, uint8_t *xram) {
    instruction_t instruction;

    uint8_t opcode;
    uint8_t operand;

    iram_reg_t reg;
    uint8_t addr;

    while (true) {
        opcode = xram_read(xram, cpu->pc);
        instruction = instructions[opcode];

        if (!instruction.implementation) {
            fprintf(stderr, "Unimplemented instruction: %02x at %04x\n", opcode, cpu->pc);
			return EXIT_FAILURE;
		}

        printf("0x%02x | PC: 0x%04x\n", opcode, cpu->pc);
        
        switch (instruction.addressing_mode) {
            case ADDRESSING_IMMEDIATE:
                operand = xram_read(xram, ++cpu->pc);

                instruction.implementation(cpu, operand, xram); 
                break;
            case ADDRESSING_REGISTER:
                reg = opcode & 0b111; // R0-R7
                operand = iram_read_register(cpu, reg);

                instruction.implementation(cpu, operand, xram);
                break;
            case ADDRESSING_DIRECT:
                addr = xram_read(xram, ++cpu->pc);

                if (addr >= 0x80) {
                    operand = sfr_read_register(cpu, addr);
                } else {
                    operand = iram_read(cpu, addr);
                }

                instruction.implementation(cpu, operand, xram);
                break;
            case ADDRESSING_REGISTER_INDIRECT:
                reg = opcode & 0b1; // R0 or R1
                addr = iram_read_register(cpu, reg);
                operand = xram_read(xram, (uint16_t)addr);

                instruction.implementation(cpu, operand, xram);
                break;
            case ADDRESSING_INDEXED:
                break;
            case ADDRESSING_IMPLICIT:
                instruction.implementation(cpu, 0, xram);
                break;
        }
        cpu->pc++;
    }
    return EXIT_SUCCESS;
}