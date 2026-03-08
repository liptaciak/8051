#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "cpu.h"
#include "memory.h"
#include "instructions.h"

#define CLR_RESET "\x1b[0m"
#define CLR_LABEL "\x1b[90m"
#define CLR_VALUE "\x1b[93m"

static uint8_t *cpu_resolve_dst(cpu_t *cpu, uint8_t *rom, instruction_t instruction) {
    switch (instruction.dst_addressing_mode) {
        case ADDRESSING_IMPLICIT:
            return sfr_ptr_register(cpu, REGISTER_ACC);

        case ADDRESSING_DIRECT: {
            uint8_t addr = memory_read(rom, ++cpu->pc);
            return &cpu->ram[addr];
        }

        case ADDRESSING_REGISTER: {
            iram_reg_t reg = instruction.opcode & 0b111; // R0-R7
            return iram_ptr_register(cpu, reg);
        }

        case ADDRESSING_REGISTER_INDIRECT: {
            iram_reg_t reg = instruction.opcode & 0b1;
            uint8_t addr = iram_read_register(cpu, reg);

            return &cpu->ram[addr];
        }

        case ADDRESSING_BIT:
        case ADDRESSING_INDEXED:
        default:
            fprintf(stderr, "Unimplemented addressing mode %d at %04x\n", instruction.dst_addressing_mode, cpu->pc);
            exit(EXIT_FAILURE);
    }
}

static uint8_t cpu_resolve_src(cpu_t *cpu, uint8_t *rom, instruction_t instruction) {
    switch (instruction.src_addressing_mode) {
        case ADDRESSING_IMPLICIT:
            return sfr_read_register(cpu, REGISTER_ACC);

        case ADDRESSING_IMMEDIATE:
            return memory_read(rom, ++cpu->pc);

        case ADDRESSING_DIRECT: {
            uint8_t addr = memory_read(rom, ++cpu->pc);
            return iram_read(cpu, addr);
        }

        case ADDRESSING_REGISTER: {
            iram_reg_t reg = instruction.opcode & 0b111; // R0-R7
            return iram_read_register(cpu, reg);
        }

        case ADDRESSING_REGISTER_INDIRECT: {
            iram_reg_t reg = instruction.opcode & 0b1; // R0 or R1
            uint8_t addr = iram_read_register(cpu, reg);

            return iram_read(cpu, addr);
        }

        case ADDRESSING_BIT:
        case ADDRESSING_INDEXED:
        default:
            fprintf(stderr, "Unimplemented addressing mode %d at %04x\n", instruction.dst_addressing_mode, cpu->pc);
            exit(EXIT_FAILURE);
    }
}

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
    uint8_t *dst = cpu_resolve_dst(cpu, rom, instruction);
    uint8_t src = cpu_resolve_src(cpu, rom, instruction);

    instruction.implementation(cpu, instruction, dst, src);

    printf(instruction.format, src);

    printf(
        "\n\n"
        CLR_LABEL "A  = " CLR_VALUE "0x%02x" CLR_LABEL " | B  = " CLR_VALUE "0x%02x\n"
        CLR_LABEL "R0 = " CLR_VALUE "0x%02x" CLR_LABEL " | R1 = " CLR_VALUE "0x%02x\n"
        CLR_LABEL "R2 = " CLR_VALUE "0x%02x" CLR_LABEL " | R3 = " CLR_VALUE "0x%02x\n"
        CLR_LABEL "R4 = " CLR_VALUE "0x%02x" CLR_LABEL " | R5 = " CLR_VALUE "0x%02x\n"
        CLR_LABEL "R6 = " CLR_VALUE "0x%02x" CLR_LABEL " | R7 = " CLR_VALUE "0x%02x\n" CLR_RESET,
        sfr_read_register(cpu, REGISTER_ACC),
        sfr_read_register(cpu, REGISTER_B),
        iram_read_register(cpu, REGISTER_R0), iram_read_register(cpu, REGISTER_R1),
        iram_read_register(cpu, REGISTER_R2), iram_read_register(cpu, REGISTER_R3),
        iram_read_register(cpu, REGISTER_R4), iram_read_register(cpu, REGISTER_R5),
        iram_read_register(cpu, REGISTER_R6), iram_read_register(cpu, REGISTER_R7)
    );
}

int cpu_execute_program(cpu_t *cpu, uint8_t *rom) {
    while (true) {
        uint8_t opcode = memory_read(rom, cpu->pc);

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