#ifndef __CPU_H__
#define __CPU_H__

#include <stdint.h>
#include <stdbool.h>

/*
 * General purpose registers
 * 32 of these registers are stored
 * in 4 register windows inside of IRAM
 */
enum iram_reg {
    REGISTER_R0,
    REGISTER_R1,
    REGISTER_R2,
    REGISTER_R3,
    REGISTER_R4,
    REGISTER_R5,
    REGISTER_R6,
    REGISTER_R7
};

enum sfr_reg {
    REGISTER_P0   = 0x80,  // Port 0
    REGISTER_SP   = 0x81,  // Stack pointer
    REGISTER_DPL  = 0x82,  // Lower 8 bits of DPTR
    REGISTER_DPH  = 0x83,  // Higher 8 bits of DPTR
    REGISTER_PCON = 0x87,  // Power control register
    REGISTER_TCON = 0x88,  // Timer 0/1 control register
    REGISTER_TMOD = 0x89,  // Timer operation mode
    REGISTER_TL0  = 0x8A,  // Lower 8 bits of Timer 0
    REGISTER_TL1  = 0x8B,  // Lower 8 bits of Timer 1
    REGISTER_TH0  = 0x8C,  // Higher 8 bits of Timer 0
    REGISTER_TH1  = 0x8D,  // Higher 8 bits of Timer 1
    REGISTER_P1   = 0x90,  // Port 1
    REGISTER_SCON = 0x98,  // Serial I/O control
    REGISTER_SBUF = 0x99,  // Serial I/O buffer
    REGISTER_P2   = 0xA0,  // Port 2
    REGISTER_IE   = 0xA8,  // Interrupt Enable
    REGISTER_P3   = 0xB0,  // Port 3
    REGISTER_IP   = 0xC0,  // Interrupt Priority
    REGISTER_PSW  = 0xD0,  // Program Status Word
    REGISTER_ACC  = 0xE0,  // Accumulator
    REGISTER_B    = 0xF0   // Additional register (used for MUL/DIV)
};

struct cpu {
    uint16_t pc;           // Program Counter

    uint8_t ram[0x80];     // IRAM
    /* 0x00-0x7F Label Description
     *  0x00-0x1F R0-R7 Register Windows
     *  0x20-0x2F       128 1-bit registers (00-7F)
     *  0x30-0x7F       General purpose RAM
     */

    uint8_t sfr[0x80];     // SFR
    /* 0x80-0xFF Special Function Registers 
     *  Addresses divisible by 8 are bit-addressable
     */
};  

enum pcon {
    PCON_IDL  =    1 << 0, // Idle mode
    PCON_PD   =    1 << 1, // Power down
    PCON_GF0  =    1 << 2, // General purpose flag bit 0
    PCON_GF1  =    1 << 3, // General purpose flag bit 1
    PCON_SMOD =    1 << 7  // Double baud rate
};

enum tcon {
    TCON_IT0 =     1 << 0, // Interrupt 0 type control
    TCON_IE0 =     1 << 1, // External interrupt 0 edge (Hardware)
    TCON_IT1 =     1 << 2, // Interrupt 1 type control
    TCON_IE1 =     1 << 3, // External interrupt 1 edge (Hardware)
    TCON_TR0 =     1 << 4, // Timer 0 run control
    TCON_TF0 =     1 << 5, // Timer 0 overflow (Hardware)
    TCON_TR1 =     1 << 6, // Timer 1 run control
    TCON_TF1 =     1 << 7  // Timer 1 overflow (Hardware)
};

enum tmod {
    TMOD_T0_M0   = 1 << 0, // Timer 0 selection bit 0
    TMOD_T0_M1   = 1 << 1, // Timer 0 selection bit 1
    TMOD_T0_CT   = 1 << 2, // Timer 0 timer or Counter selector
    TMOD_T0_GATE = 1 << 3, // Timer 0 start/stop timers by hardware
    TMOD_T1_M0   = 1 << 4, // Timer 1 selection bit 0
    TMOD_T1_M1   = 1 << 5, // Timer 1 selection bit 1
    TMOD_T1_CT   = 1 << 6, // Timer 1 timer or Counter selector
    TMOD_T1_GATE = 1 << 7  // Timer 1 start/stop timers by hardware
};

enum scon {
    SCON_RI  =     1 << 0, // Set when a byte was received and placed in SBUF
    SCON_TI  =     1 << 1, // Set after finishing transfer of 8-bit character
    SCON_RB8 =     1 << 2, // Receive bit 8
    SCON_TB8 =     1 << 3, // Transmit bit 8
    SCON_REN =     1 << 4, // Receiver enable/disable 
    SCON_SM2 =     1 << 5, // Enables multiprocessor communication in modes 2 and 3
    SCON_SM1 =     1 << 6, // Serial mode selection bit 0
    SCON_SM0 =     1 << 7  // Serial mode selection bit 1
};

enum ie {
    IE_EX0 =       1 << 0, // Enable/Disable external interrupt 0
    IE_ET0 =       1 << 1, // Enable/Disable timer 0 overflow interrupt
    IE_EX1 =       1 << 2, // Enable/Disable external interrupt 1
    IE_ET1 =       1 << 3, // Enable/Disable timer 1 overflow interrupt
    IE_ES  =       1 << 4, // Enable/Disable serial port interrupt
    IE_EA  =       1 << 7  // Enable/Disable global interrupts
};

enum p3 {
    P3_RXD  =      1 << 0, // Received serial data signal
    P3_TXD  =      1 << 1, // Transmits serial data signal
    P3_INT0 =      1 << 2, // External interrupt 0 signal
    P3_INT1 =      1 << 3, // External interrupt 1 signal
    P3_T0   =      1 << 4, // External input to timer 0 singal
    P3_T1   =      1 << 5, // External input to timer 1 signal
    P3_WR   =      1 << 6, // External memory write signal
    P3_RD   =      1 << 7  // External memory read signal
};

enum ip {
    IP_PX0 =       1 << 0, // Defines external interrupt 0 priority level
    IP_PT0 =       1 << 1, // Defines timer 0 overflow interrupt priority level
    IP_PX1 =       1 << 2, // Defines external interrupt 1 priority level
    IP_PT1 =       1 << 3, // Defines timer 1 overflow interrupt priority level
    IP_PS  =       1 << 4  // Defines serial port interrupt priority level
};

enum psw {
    PSW_P   =      1 << 0, // Parity flag
    PSW_OV  =      1 << 2, // Overflow flag
    PSW_RS0 =      1 << 3, // Register bank select bit 0
    PSW_RS1 =      1 << 4, // Register bank select bit 1
    PSW_F0  =      1 << 5, // General purpose flag bit
    PSW_AC  =      1 << 6, // Auxiliary carry flag
    PSW_CY  =      1 << 7  // Carry flag
};

void cpu_reset(struct cpu* cpu);
void cpu_execute_program(struct cpu* cpu, uint8_t* memory);

#endif /* ! __CPU_H__ */