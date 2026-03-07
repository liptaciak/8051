#ifndef __INSTRUCTIONS_MOV_H__
#define __INSTRUCTIONS_MOV_H__

void mova(cpu_t *cpu, instruction_t instruction, uint8_t *operands);
void movr(cpu_t *cpu, instruction_t instruction, uint8_t *operands);
void movadr(cpu_t *cpu, instruction_t instruction, uint8_t *operands);
void movri(cpu_t *cpu, instruction_t instruction, uint8_t *operands);

#endif /* ! __INSTRUCTIONS_MOV_H__ */