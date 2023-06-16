#include "../include/nes.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <SDL2/SDL.h>

// CLOCK AND DERIVATIVES
#define CLK_MASTER (int) round(236250000 / 11.0)
#define CLK_CPU (int) round(CLK_MASTER / 12.0)

// PICTURE PROPERTIES
#define HEIGHT 240
#define WIDTH 256

#define FRAME_RATE 60.0988

// Palette and Color Matrix
uint32_t colors[64];

// CBuff and 4*CBuff
uint32_t cbuff[HEIGHT*WIDTH];

int main (int argc, char** argv)
{
    if (argc < 3)
    {
        printf ("Invalid Use of Executable.\n\t./build <rom-filename> <palette-filename>\n");
        return 1;
    }

    // Load PALETTE into Color Matrix
    int palette_len = strlen (argv[2]);
    const char *palette_ext = &argv[2][palette_len - 4];
    if (strcmp(palette_ext, ".pal") != 0)
    {
        printf ("Invalid .pal file Input, Please use a Valid .pal file\n"); 
        return 1;
    }
    else {
        printf ("Valid .pal file Input\n");
    }
    FILE* palette_file = fopen(argv[2], "rb");
    if (palette_file == NULL)
    {
        printf ("Error Opening Palette File. Check File Path.\n");
        exit(1);
    }
    uint8_t* temp_color_buff = (uint8_t*) malloc ((192)*sizeof(uint8_t));
    fread (temp_color_buff, 1, 192, palette_file);
    fclose (palette_file);
    for (int i=0; i<64; i++) {
        colors[i] = (((temp_color_buff[i*3]) | (temp_color_buff[i*3+1] << 8)) | (temp_color_buff[i*3+2] << 16)) | (0xFF << 24);
    }
    free (temp_color_buff);

    // Create NES and Load a ROM
    NES* bignes = create_nes(colors);
    load_rom (bignes, argv[1]);
    
    printf ("CPU CLOCK: %d\n", CLK_CPU);
    printf ("NANOSECONDS PER CLOCK: %lf\n", 1000000000.0 / CLK_CPU);

    struct timespec clk, rm = {0, (long) 1000000000.0 / CLK_CPU};

    init_nes (bignes, clk, rm);
    
    destroy_nes (bignes);
    return 0;
}