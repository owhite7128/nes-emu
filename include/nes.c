#include "nes.h"
#include "cpu.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

NES* create_nes (uint32_t colors[64])
{
    NES* ret = (NES*) malloc (1*sizeof(NES));
    ret->NES_CPU = new_cpu();
    ret->NES_PPU = new_ppu();
    ret->NES_CPU->ppu = ret->NES_PPU;
    ret->RLOAD = 0;
    for (int i=0; i<64; i++)
    {
        ret->NES_PPU->COLORS[i] = colors[i];
    }

    return ret;
}

void destroy_nes (NES* nes)
{
    delete_cpu (nes->NES_CPU);
    delete_ppu (nes->NES_PPU);
    free (nes->NES_CPU);
    free (nes->NES_PPU);

    free (nes);
}

void load_rom (NES* nes, char* fname)
{
    int fname_len = strlen (fname);
    const char *fname_ext = &fname[fname_len - 4];
    if (!(strcmp(fname_ext, ".nes") == 0 || strcmp(fname_ext, ".NES") == 0))
    {
        printf ("Invalid .NES file Input, Please use a Valid .NES file\n"); 
        exit(1);
    }
    else {
        printf ("Valid .NES file Input\n");
    }

    FILE* in_file = fopen (fname, "rb");
    if (in_file == NULL)
    {
        printf ("Error Opening ROM File. Check File Path.\n");
        exit(1);
    }
    uint8_t header[16];
    fread (header, 1, 16, in_file);

    uint16_t pgr_sz = header[4] * 0x4000;
    uint16_t chr_sz = header[5] * 0x2000;
    uint8_t mirror = ( header[6] | 0xfe ) - 0xfe;

    uint8_t mapper = (((header[7]>>4)<<4) | (header[6]>>4));

    printf ("Mapper: %0#04x, Mirror: %0#04x\n", mapper, mirror);


    if (mapper == 0x0) {
        // $4020 – $FFFF Cartridge space: PRG ROM, PRG RAM, and mapper registers (see note)
        // $4020 - $5FFF Unused
        // $6000 - $7FFF PGR RAM
        // $8000 - $BFFF First 16 KiB of PGR ROM 
        // $C000 - $FFFF Last 16 KiB of PGR ROM (if NROM-256) otherwise, mirror of $8000 - $BFFF


        uint16_t PGR_ROM_OFF = 0x8000;
        uint16_t CHR_ROM_OFF = 0x0;
        
        uint8_t *temp_buff_pgr = (uint8_t*) malloc((pgr_sz)*sizeof(uint8_t));
        uint8_t *temp_buff_chr = (uint8_t*) malloc((chr_sz)*sizeof(uint8_t));
        fread (temp_buff_pgr, 1, pgr_sz, in_file);
        fread (temp_buff_chr, 1, chr_sz, in_file);

        

        for (int i=0; i<pgr_sz; i++) {
            nes->NES_CPU->RAM[i+PGR_ROM_OFF] = temp_buff_pgr[i];
        }
        if (pgr_sz == 0x4000) {
            for (int i=0; i<pgr_sz; i++) {
                nes->NES_CPU->RAM[i+PGR_ROM_OFF+0x4000] = temp_buff_pgr[i];
            }
        }

        if (mirror == 0x1) {
            // Veritcal (Horizontal Arrangement)

        } else {
            // Horizontal (Vertical Arrangement)
        }

        for (int i=0; i<chr_sz; i++) {
            nes->NES_PPU->RAM[i+0x0] = temp_buff_chr[i];
        }
        free (temp_buff_pgr);
        free (temp_buff_chr);
    } else {
        printf ("Error: Unsupported Mapper of Type: %0#0x (Lookup https://www.nesdev.org/wiki/Mapper to find corresponding Mapper)\n", mapper);
        exit (1);
    }

    fclose (in_file);
    nes->RLOAD = 1;
    return;
}

void init_nes (NES* nes, struct timespec t1, struct timespec t2) {
    if (nes->RLOAD == 0)
    {
        printf ("Error: No ROM is Loaded, Please Call `load_rom (<NES>, <ROM-FILENAME>);`");
        exit (1);
    }
    int stpcnt = 0;
    while (stpcnt < 100000)
    {
        // NEED TO START TIMER UP HERE AND THEN ACTUALLY CHECK NSECONDS SINCE ELAPSE TO GET ACCURATE TIMING
        

        // 3 PPU Steps
        ppu_step (nes->NES_PPU);
        ppu_step (nes->NES_PPU);
        ppu_step (nes->NES_PPU);

        // 1 CPU Step
        cpu_step (nes->NES_CPU);

        nanosleep (&t1, &t2);
        stpcnt++;
    }

}