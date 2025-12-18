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

    while (true) {
        opcode = xram_read(xram, cpu->pc);
        instruction = instructions[opcode];

        if (!instruction.implementation) {
            fprintf(stderr, "Unimplemented instruction: %02x at %04x\n", opcode, cpu->pc);
			return EXIT_FAILURE;
		}

        printf("\n0x%02x | PC: 0x%04x\n", opcode, cpu->pc);
        
        switch (instruction.addressing_mode) {
            case ADDRESSING_IMPLICIT:
                instruction.implementation(cpu, opcode, nullptr, xram);
                break;

            case ADDRESSING_IMMEDIATE:
                operand = xram_read(xram, ++cpu->pc);
                instruction.implementation(cpu, opcode, &operand, xram); 
                break;

            case ADDRESSING_DIRECT:
                operand = xram_read(xram, ++cpu->pc);
                instruction.implementation(cpu, opcode, &operand, xram);
                break;

            case ADDRESSING_REGISTER: {
                iram_reg_t reg = opcode & 0b111; // R0-R7

                /* 
                 * We don't know the destination but the only possible sources 
                 * are R0-R7 registers or the A register
                 */
                operand = iram_read_register(cpu, reg);
                instruction.implementation(cpu, opcode, &operand, xram);
                break;
            }

            case ADDRESSING_REGISTER_INDIRECT: {
                iram_reg_t reg = opcode & 0b1; // R0 or R1

                /* 
                 * We don't know the destination but the only possible sources 
                 * are R0 or R1 registers or the A register
                 */
                operand = iram_read_register(cpu, reg);
                instruction.implementation(cpu, opcode, &operand, xram);
                break;
            }

            case ADDRESSING_BIT:
                fprintf(stderr, "Unimplemented instruction: %02x at %04x\n", opcode, cpu->pc);
			    return EXIT_FAILURE;

            case ADDRESSING_INDEXED:
                fprintf(stderr, "Unimplemented instruction: %02x at %04x\n", opcode, cpu->pc);
			    return EXIT_FAILURE;
        }
        cpu->pc++;
    }
    
    return EXIT_SUCCESS;
}