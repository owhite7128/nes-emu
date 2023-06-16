#ifndef CPU_H
#define CPU_H

#include <stdlib.h>
#include "ppu.h"

typedef struct cpu_struct {
    // RAM
    uint8_t* RAM;

    // Registers
    uint8_t A;
    uint8_t X;
    uint8_t Y;
    uint16_t PC;
    uint8_t S;
    uint8_t P;

    // Interrupts
    uint8_t NMI;
    uint8_t RST;

    // Link to PPU.
    PPU* ppu;

    uint8_t skip_cycles;
} CPU;

CPU* new_cpu ();

void delete_cpu (CPU* cpu);

void cpu_step (CPU* cpu);

#endif