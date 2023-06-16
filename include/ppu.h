#ifndef PPU_H
#define PPU_H

#include <stdlib.h>
#include <SDL2/SDL.h>

typedef struct ppu_struct {
    // SDL
    SDL_Window* window;
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    // CBUFF
    uint32_t BUFF[240*256];

    // Colors 
    uint32_t COLORS[64];

    // VRAM
    uint8_t* RAM;

    // Sprite Memory
    uint8_t* OAM;
    uint8_t* SOAM;
    uint8_t PTAB_SP[16];
    uint8_t LATCH;
    uint8_t SPX[8];

    // Background Memory
    uint16_t ADDR;
    uint16_t TEMP_ADDR;
    uint16_t SH_PTD[2];
    uint8_t SH_PA[2];

    // Registers
    uint8_t CTRL;
    uint8_t MASK;
    uint8_t STAT;

    // Scroll
    uint16_t SCRL;

    // Counters
    uint16_t LINECNT;
    uint16_t CYCLECNT;

    // Even-Odd Frame
    uint8_t ODDNESS;

    uint8_t VBLANK;
} PPU;

PPU* new_ppu ();

/* void PPU_CTRL_W (PPU* ppu, uint8_t byte);
void PPU_MASK_W (PPU* ppu, uint8_t byte);
uint8_t PPU_STAT_R (PPU* ppu, );
void PPU_OAMADDR_W (PPU* ppu, uint8_t byte);
void PPU_OAMDATA_W (PPU* ppu, uint8_t byte);
uint8_t PPU_OAMDATA_R (PPU* ppu, );
void PPU_SCROLL_W (PPU* ppu, uint8_t xscroll, uint8_t yscroll);
void PPU_ADDR_W (PPU* ppu, uint8_t lbyte, uint8_t hbyte);
void PPU_DATA_W (PPU* ppu, uint8_t byte);
uint8_t PPU_DATA_R (PPU* ppu, );
void PPU_OAMDMA_W (PPU* ppu, uint8_t byte); */

void delete_ppu (PPU* ppu);

void ppu_step (PPU* ppu);

#endif