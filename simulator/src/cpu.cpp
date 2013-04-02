#include "cpu.hpp"

void CPU::read_program (char* filename)
{
    FILE* bin_file;
    bin_file = fopen(filename, "rb");
    bus_pc = 0;
    while (!feof(bin_file)) {
        fread(&pm_in, 4, 1, bin_file);
        if (ferror(bin_file)) {
            break;
        }
        program_memory -> store();
        bus_pc++;
    }
    bus_pc = 0;
}

