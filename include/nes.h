#ifndef NES_H
#define NES_H

#include "cpu.h"
#include "ppu.h"
#include <stdlib.h>
#include <time.h>

typedef struct nes_struct {
    CPU* NES_CPU;
    PPU* NES_PPU;

    int RLOAD;
} NES;

NES* create_nes (uint32_t colors[64]);

void destroy_nes (NES* nes);

void load_rom (NES* nes, char* fname);

void init_nes (NES* nes, struct timespec t1, struct timespec t2);

#endif