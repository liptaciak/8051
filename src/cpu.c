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

void cpu_execute_instruction(cpu_t *cpu, uint8_t *rom, instruction_t instruction) {
    uint8_t operand;

    switch (instruction.addressing_mode) {
        case ADDRESSING_IMPLICIT:
            operand = sfr_read_register(cpu, REGISTER_ACC);

            instruction.implementation(cpu, instruction, &operand);
            break;

        case ADDRESSING_IMMEDIATE:
            operand = memory_read(rom, ++cpu->pc);
            instruction.implementation(cpu, instruction, &operand); 
            break;

        case ADDRESSING_DIRECT:
            operand = memory_read(rom, ++cpu->pc);
            operand = iram_read(cpu, operand);

            instruction.implementation(cpu, instruction, &operand);
            break;

        case ADDRESSING_REGISTER: {
            iram_reg_t reg = opcode & 0b111; // R0-R7
            
            operand = iram_read_register(cpu, reg);
            instruction.implementation(cpu, instruction, &operand);
            break;
        }

        case ADDRESSING_REGISTER_INDIRECT: {
            iram_reg_t reg = opcode & 0b1; // R0 or R1

            operand = iram_read_register(cpu, reg);
            operand = iram_read(cpu, operand);

            instruction.implementation(cpu, instruction, &operand);
            break;
        }

        // Unimplemented addressing modes
        case ADDRESSING_BIT:
            operand = memory_read(rom, ++cpu->pc);
            instruction.implementation(cpu, instruction, &operand);
            break;

        case ADDRESSING_INDEXED:
            instruction.implementation(cpu, instruction, nullptr);
            break;
    }
}

int cpu_execute_program(cpu_t *cpu, uint8_t *rom) {
    while (true) {
        instruction_t instruction = instructions[opcode];
        instruction.opcode = opcode;

        if (!instruction.implementation) {
            fprintf(stderr, "Unimplemented instruction: %02x at %04x\n", opcode, cpu->pc);
			return EXIT_FAILURE;
		}

        printf("\n0x%02x | PC: 0x%04x\n", opcode, cpu->pc);
        
        cpu_execute_instruction(cpu, rom, instruction);
        cpu->pc++;
    }
    
    return EXIT_SUCCESS;
}