#include "cpu.h"
#include "memory.h"

#include "instructions.h"

/* 
 * MOV A, ?
 *   Addressing: Immediate, Direct, Register, Register Indirect
 *   Flags: P
 */
void mova(cpu_t *cpu, instruction_t instruction, uint8_t *operand) {
    // TODO: Implement Parity flag

    sfr_write_register(cpu, REGISTER_ACC, *operand);
    printf("MOV A, 0x%02x\n", *operand);
}

/* 
 * MOV Rn, ?
 *   Addressing: Immediate, Direct, Implicit
 *   Flags: None
 */
void movr(cpu_t *cpu, instruction_t instruction, uint8_t *operand) {
    iram_reg_t reg = instruction.opcode & 0b111;
    
    iram_write_register(cpu, reg, *operand);
    printf("MOV R%d, 0x%02x\n", reg, *operand);
}

/* 
 * MOV (adr), ?
 *   Addressing: Implicit, Immediate, Direct, Register Indirect
 *   Flags: None
 */
void movadr(cpu_t *cpu, instruction_t instruction, uint8_t *operand) {
    // TODO: Implementation

    printf("MOV 0x%02x, 0x%02x\n", *operand, value);
}

/* 
 * MOV @RI, ?
 *   Addressing: Implicit, Immediate, Direct
 *   Flags: None
 */
void movri(cpu_t *cpu, instruction_t instruction, uint8_t *operand) {
    iram_reg_t reg = instruction.opcode & 0b1;
    printf("MOV @R%d, 0x%02x\n", reg, *operand);
}