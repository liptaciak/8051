#ifndef __CPU_H__
#define __CPU_H__

#include <stdint.h>

struct cpu_state {
    uint16_t pc; // Program Counter

    uint8_t ram[0x80]; // IRAM
    /* 0x00-0x7F Label Description
     * 0x00-0x1F R0-R7 Register Windows
     * 0x20-0x2F       128 1-bit registers (00-7F)
     * 0x30-0x7F       General purpose RAM
     */

    uint8_t sfr[0x80]; // SFR
    /* 0x80–0xFF Label (Most to least significant bit)     Description
     * 0x80      P0                                        Port 0
     * 0x81      SP                                        Stack pointer
     * 0x82      DPL                                       Lower 8 bits of DPTR
     * 0x83      DPH                                       Higher 8 bits of DPTR
     * 0x87      PCON  (SMOD - - - GF1 GF0 PD IDL)         Power control register
     * 0x88      TCON  (TF1 TR1 TF0 TR0 IE1 IT1 IE0 IT0)   Timer 0/1 control register
     * 0x89      TMOD  (GATE C/T M1 M0 GATE C/T M1 M0)     Timer operation mode
     * 0x8A      TL0                                       Lower 8 bits of Timer 0
     * 0x8B      TL1                                       Lower 8 bits of Timer 1
     * 0x8C      TH0                                       Higher 8 bits of Timer 0
     * 0x8D      TH1                                       Higher 8 bits of Timer 1
     * 0x90      P1                                        Port 1
     * 0x98      SCON  (SM0 SM1 SM2 REN TB8 RB8 TI RI)     Serial I/O control
     * 0x99      SBUF                                      Serial I/O buffer
     * 0xA0      P2                                        Port 2
     * 0xA8      IE    (EA - - ES ET1 EX1 ET0 EX0)         Interrupt Enable
     * 0xB0      P3    (/RD /WR T1 T0 /INT1 /INT0 TxD RxD) Port 3
     * 0xC0      IP    (- - - PS PT1 PX1 PT0 PX0)          Interrupt Priority
     * 0xD0      PSW   (CY AC F0 RS1 RS0 OV - P)           Program Status Word
     * 0xE0      ACC                                       Accumulator
     * 0xF0      B                                         Additional register (used for MUL/DIV)
     */
};  

enum pcon {
    PCON_IDL  =  1 << 0,
    PCON_PD   =  1 << 1,
    PCON_GF0  =  1 << 2,
    PCON_GF1  =  1 << 3,
    PCON_SMOD =  1 << 7
};

enum tcon {
    TCON_IT0 =   1 << 0,
    TCON_IE0 =   1 << 1,
    TCON_IT1 =   1 << 2,
    TCON_IE1 =   1 << 3,
    TCON_TR0 =   1 << 4,
    TCON_TF0 =   1 << 5,
    TCON_TR1 =   1 << 6,
    TCON_TF1 =   1 << 7
};

enum tmod {
    TMOD_M00   = 1 << 0,
    TMOD_M10   = 1 << 1,
    TMOD_CT0   = 1 << 2,
    TMOD_GATE0 = 1 << 3,
    TMOD_M01   = 1 << 4,
    TMOD_M11   = 1 << 5,
    TMOD_CT    = 1 << 6,
    TMOD_GATE1 = 1 << 7
};

enum scon {
    SCON_RI  =   1 << 0,
    SCON_TI  =   1 << 1,
    SCON_RB8 =   1 << 2,
    SCON_TB8 =   1 << 3,
    SCON_REN =   1 << 4,
    SCON_SM2 =   1 << 5,
    SCON_SM1 =   1 << 6,
    SCON_SM0 =   1 << 7
};

enum ie {
    IE_EX0 =     1 << 0,
    IE_ET0 =     1 << 1,
    IE_EX1 =     1 << 2,
    IE_ET1 =     1 << 3,
    IE_ES  =     1 << 4,
    IE_EA  =     1 << 7 
};

enum p3 {
    P3_RXD  =    1 << 0,
    P3_TXD  =    1 << 1,
    P3_INT0 =    1 << 2,
    P3_INT1 =    1 << 3,
    P3_T0   =    1 << 4,
    P3_T1   =    1 << 5,
    P3_WR   =    1 << 6,
    P3_RD   =    1 << 7
};

enum ip {
    IP_PX0 =     1 << 0,
    IP_PT0 =     1 << 1,
    IP_PX1 =     1 << 2,
    IP_PT1 =     1 << 3,
    IP_PS  =     1 << 4
};

enum psw {
    PSW_P   =    1 << 0,
    PSW_OV  =    1 << 2,
    PSW_RS0 =    1 << 3,
    PSW_RS1 =    1 << 4,
    PSW_F0  =    1 << 5,
    PSW_AC  =    1 << 6,
    PSW_CY  =    1 << 7
};

#endif /* ! __CPU_H__ */