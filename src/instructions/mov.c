#include "cpu.h"
#include "memory.h"

#include "instructions.h"

// MOV A, ? - Immediate, Direct, Register Indirect, Implicit
void mova(cpu_t *cpu, uint8_t opcode, uint8_t *operand, uint8_t *) {
    sfr_write_register(cpu, REGISTER_ACC, *operand);
    printf("MOV A, 0x%02x\n", *operand);
}

// MOV Rn, ? - Immediate, Direct, Implicit
void movr(cpu_t *cpu, uint8_t opcode, uint8_t *operand, uint8_t *) {
    iram_reg_t reg = opcode & 0b111;
    uint8_t value = operand ? *operand : sfr_read_register(cpu, REGISTER_ACC);

    iram_write_register(cpu, reg, value);
    printf("MOV R%d, 0x%02x\n", reg, *operand);
}

// MOV (adr), ? - Direct + Implicit, Immediate, Register Indirect, Direct
void movadr(cpu_t *cpu, uint8_t opcode, uint8_t *operand, uint8_t *) {
    uint8_t value = operand ? *operand : sfr_read_register(cpu, REGISTER_ACC);

    iram_write(cpu, *operand, value);
    printf("MOV 0x%02x, 0x%02x\n", addr, *operand);
}

// MOV @Ri, ? - Register Indirect
// MOV DPTR, ? - Direct Extended