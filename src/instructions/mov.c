#include "cpu.h"
#include "instructions.h"

/* 
 * MOV A, ?
 *   Addressing: Immediate, Direct, Register, Register Indirect
 *   Flags: P
 * MOV Rn, ?
 *   Addressing: Immediate, Direct, Implicit
 *   Flags: None
 * MOV (adr), ?
 *   Addressing: Implicit, Immediate, Direct, Register Indirect
 *   Flags: None
 * MOV @RI, ?
 *   Addressing: Implicit, Immediate, Direct
 *   Flags: None
 */
void mov(cpu_t *cpu, instruction_t instruction, uint8_t *dst, uint8_t src) {
    // TODO: Handle parity flag for MOV A, ?
    *dst = src;
}