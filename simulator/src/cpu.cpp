#include "cpu.hpp"
#include <iostream>
#include <cstdio>
#include <cstdlib>

using namespace std;

void CPU::read_program(char* filename)
{
    FILE* bin_file;
    bin_file = fopen(filename, "rb");
    if (!bin_file)
    {
        std::cerr << "Erreur : le fichier " << filename << " n'existe pas." << std::endl;
        exit(1);
    }
    bus_pc = 0;
    while (!feof(bin_file))
    {
        fread(&pm_in, 4, 1, bin_file);
        if (ferror(bin_file))
        {
            break;
        }
        program_memory -> store();
        bus_pc++;
    }
    pm_in = -1;
    program_memory->store();
    bus_pc = 0;
    fclose(bin_file);
}

void CPU::cycle()
{

    control_unit->read_inst();
    control_unit->decode_inst();
    control_unit->execute_inst();

}

void CPU::run()
{

    while (getBus_inst() != -1)
    {
        cycle();

    }
}

