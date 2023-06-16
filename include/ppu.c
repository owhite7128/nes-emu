#include "ppu.h"
#include <stdlib.h>
#include <SDL2/SDL.h>

PPU* new_ppu ()
{
    PPU* ret = (PPU*) malloc (1*sizeof(PPU));
    ret->OAM = (uint8_t*) malloc (256*sizeof(uint8_t));
    // 64 Slots of 4 Byte Chunks
    // 0 Byte - Y Pos of Top 
    // 1 Byte - 
    // 2 Byte - 
    // 3 Byte - X Pos of Left Side

    ret->SOAM = (uint8_t*) malloc (32*sizeof(uint8_t));
    // Secondary OAM, for use each in each scanline.

    ret->RAM = (uint8_t*) malloc (16384*sizeof(uint8_t)); 
    // MAP
    // $0000 - $0FFF	$1000	Pattern table 0
    // $1000 - $1FFF	$1000	Pattern table 1
    // $2000 - $23FF	$0400	Nametable 0
    // $2400 - $27FF	$0400	Nametable 1
    // $2800 - $2BFF	$0400	Nametable 2
    // $2C00 - $2FFF	$0400	Nametable 3
    // $3000 - $3EFF	$0F00	Mirrors of $2000-$2EFF
    // $3F00 - $3F1F    $0020	Palette RAM indexes
    // $3F20 - $3FFF	$00E0	Mirrors of $3F00-$3F1F

    ret->CTRL = 0;
    ret->MASK = 0;
    ret->STAT = 0;

    ret->SCRL = 0;
    ret->ADDR = 0;
    ret->TEMP_ADDR = 0;

    ret->LINECNT = 0;
    ret->CYCLECNT = 0;

    ret->ODDNESS = 0;

    // Initialize SDL2 Window with Size (Width) x (Height)
    ret->window = SDL_CreateWindow ("DEMO", SDL_WINDOWPOS_CENTERED_DISPLAY(1), SDL_WINDOWPOS_CENTERED_DISPLAY(1), 256, 240, SDL_WINDOW_ALLOW_HIGHDPI);

    ret->renderer = SDL_CreateRenderer (ret->window, -1, SDL_RENDERER_PRESENTVSYNC);

    ret->texture = SDL_CreateTexture (ret->renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, 256, 240);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        // do nothing
    }

    for (int i=0; i<(240*256); i++)
    {
        ret->BUFF[i] = 0xFF0000FF;
    }
    return ret;
}

void delete_ppu (PPU* ppu)
{
    free (ppu->OAM);
    free (ppu->RAM);
    free (ppu->SOAM);
}

// Timing
// -1 or 261 (Prerender Scanline) - 
// 0 - 239 (Visible Scanlines)
// 240 (Post Render) - Nothing Happens
// 241 - 260 (VBlank) - VBlank Flag set, OAM transfer happens here

// During 0 -239 
// Cycle 0 - Idle Cycle
// Cycles 1-256 - 
// Cycles 257-320 - 


void ppu_step (PPU* ppu)
{
    if (ppu->LINECNT < 240) 
    {
        if (ppu->CYCLECNT == 0)
        {

        } else if (ppu->CYCLECNT <= 256)
        {

        } else if (ppu->CYCLECNT <= 320)
        {

        } else if (ppu->CYCLECNT <= 336)
        {

        } else if (ppu->CYCLECNT <= 340) {

        }
    } else if (ppu->LINECNT == 240)
    {
        if (ppu->CYCLECNT == 1) {
            SDL_UpdateTexture (ppu->texture, NULL, ppu->BUFF, 256 * 4);
            SDL_RenderCopyEx (ppu->renderer, ppu->texture, NULL, NULL, 0.0, NULL, 0);
            SDL_RenderPresent (ppu->renderer);
        }
    } else if (ppu->LINECNT < 261)
    {
        if (ppu->LINECNT == 241 && ppu->CYCLECNT == 1)
        {
            ppu->VBLANK = 1;
        }
    } else if (ppu->LINECNT == 261)
    {
        if (ppu->CYCLECNT == 1)
        {
            ppu->VBLANK = 0;
        }
    }

    if (ppu->CYCLECNT == 340)
    {
        ppu->CYCLECNT = 0;
        if (ppu->LINECNT == 261)
        {
            ppu->LINECNT = 0;
        } else {
            ppu->LINECNT++;
        }
    } else {
        ppu->CYCLECNT++;
    }
    
}
