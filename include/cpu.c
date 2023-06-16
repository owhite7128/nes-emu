#include "cpu.h"
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <math.h>

// CLOCK AND DERIVATIVES
#define CLK_MASTER (int) round(236250000 / 11.0)
#define CLK_CPU (int) round(CLK_MASTER / 12.0)
#define CLK_CYCLE (unsigned long long) (1000000000.0/CLK_CPU)

CPU* new_cpu ()
{
    CPU* ret = NULL;
    ret = (CPU*) malloc (1*sizeof(CPU));
    ret->A = 0;
    ret->X = 0;
    ret->Y = 0;
    ret->PC = 0;
    ret->S = 0;
    ret->P = 0;
    
    ret->NMI = 0;
    ret->RST = 1;

    ret->RAM = (uint8_t*) malloc ((0xFFFF + 1) * sizeof(uint8_t));
    // MAP 
    // $0000 - $07FF Internal RAM
    // $0800 – $0FFF Mirror of $0000 - $07FF
    // $1000 – $17FF "
    // $1800 – $1FFF "
    // $2000 – $2007 PPU Registers
    // $2008 – $3FFF Mirrors of $2000 – $2007 (repeats every 8 bytes)
    // $4000 – $4017 NES APU and I/O registers
    // $4018 – $401F APU and I/O functionality that is normally disabled. 
    // $4020 – $FFFF Cartridge space: PRG ROM, PRG RAM, and mapper registers (see note)
    return ret;
}

void delete_cpu (CPU* cpu)
{
    free (cpu->RAM);
}

void cpu_step (CPU* cpu)
{   
    if (cpu->skip_cycles > 0)
    {
        cpu->skip_cycles--;
    } else {
        if (cpu->RST) {
            cpu->skip_cycles = 0;
            cpu->A = 0;
            cpu->X = 0;
            cpu->Y = 0;
            cpu->S = 0xfd;
            cpu->P = 0;
            cpu->P = cpu->P | 0x4;
            cpu->PC =  (cpu->RAM[0xFFFD] << 8) | (cpu->RAM[0xFFFC]);
            cpu->RST = 0;
        } else if (cpu->NMI) {
            // NMI INTERRUPT

        }else if (cpu->RAM[cpu->PC] == 0x00)
        {
            // BRK
        } else if (cpu->RAM[cpu->PC] == 0x01)
        {
            // ORA (ind,X)
            
        } else if (cpu->RAM[cpu->PC] == 0x05)
        {
            // ORA zpg   
        } else if (cpu->RAM[cpu->PC] == 0x06)
        {
            // ASL zpg
        } else if (cpu->RAM[cpu->PC] == 0x08)
        {
            // PHP
        } else if (cpu->RAM[cpu->PC] == 0x09)
        {
            // ORA #
        } else if (cpu->RAM[cpu->PC] == 0x0a)
        {
            // ASL A
        } else if (cpu->RAM[cpu->PC] == 0x0d)
        {
            // ORA abs
        } else if (cpu->RAM[cpu->PC] == 0x0e)
        {
            // ASL abs
        } else if (cpu->RAM[cpu->PC] == 0x10)
        {
            // BPL rel
        } else if (cpu->RAM[cpu->PC] == 0x11)
        {
            // ORA (ind),Y
        } else if (cpu->RAM[cpu->PC] == 0x15)
        {
            // ORA zpg,X
        } else if (cpu->RAM[cpu->PC] == 0x16)
        {
            // ASL zpg,X
        } else if (cpu->RAM[cpu->PC] == 0x18)
        {
            // CLC
        } else if (cpu->RAM[cpu->PC] == 0x19)
        {
            // ORA abs,Y
        } else if (cpu->RAM[cpu->PC] == 0x1d)
        {
            // ORA abs,X
        } else if (cpu->RAM[cpu->PC] == 0x1e)
        {
            // ASL abs,X
        } else if (cpu->RAM[cpu->PC] == 0x20)
        {
            // JMP abs
        } else if (cpu->RAM[cpu->PC] == 0x21)
        {
            // AND (ind,X)
        } else if (cpu->RAM[cpu->PC] == 0x24)
        {
            // BIT zpg
        } else if (cpu->RAM[cpu->PC] == 0x25)
        {
            // AND zpg
        } else if (cpu->RAM[cpu->PC] == 0x26)
        {
            // ROL zpg
        } else if (cpu->RAM[cpu->PC] == 0x28)
        {
            // PLP
        } else if (cpu->RAM[cpu->PC] == 0x29)
        {
            // AND #
        } else if (cpu->RAM[cpu->PC] == 0x2a)
        {
            // ROL A
        } else if (cpu->RAM[cpu->PC] == 0x2c)
        {
            // BIT abs
        } else if (cpu->RAM[cpu->PC] == 0x2d)
        {
            // AND abs
        } else if (cpu->RAM[cpu->PC] == 0x2e)
        {
            // ROL abs
        } else if (cpu->RAM[cpu->PC] == 0x30)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x31)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x35)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x36)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x38)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x39)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x3d)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x3e)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x40)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x41)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x45)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x46)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x48)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x49)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x4a)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x4c)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x4d)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x4e)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x50)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x51)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x55)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x56)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x58)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x59)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x5d)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x5e)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x60)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x61)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x65)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x66)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x68)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x69)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x6a)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x6c)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x6d)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x6e)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x70)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x71)
        {

        } else if (cpu->RAM[cpu->PC] == 0x75)
        {

        } else if (cpu->RAM[cpu->PC] == 0x76)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x78)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x79)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x7d)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x7e)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x81)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x84)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x85)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x86)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x88)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x8a)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x8c)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x8d)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x8e)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x90)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x91)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x94)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x95)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x96)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x98)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x99)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x9a)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0x9d)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xa0)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xa1)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xa2)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xa4)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xa5)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xa6)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xa8)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xa9)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xaa)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xac)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xad)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xae)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xb0)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xb1)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xb4)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xb5)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xb6)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xb8)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xb9)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xba)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xbc)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xbd)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xbe)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xc0)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xc1)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xc4)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xc5)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xc6)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xc8)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xc9)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xca)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xcc)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xcd)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xce)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xd0)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xd1)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xd5)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xd6)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xd8)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xd9)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xdd)
        {

        } else if (cpu->RAM[cpu->PC] == 0xde)
        {

        } else if (cpu->RAM[cpu->PC] == 0xe0)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xe1)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xe4)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xe5)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xe6)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xe8)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xe9)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xea)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xec)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xed)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xee)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xf0)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xf1)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xf5)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xf6)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xf8)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xf9)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xfd)
        {
            
        } else if (cpu->RAM[cpu->PC] == 0xfe)
        {
            
        } else {
            printf ("Invalid Instruction. Halting\n");
            exit (-1);
        }
        cpu->PC++;
    }
}
