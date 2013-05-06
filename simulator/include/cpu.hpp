#ifndef _CPU
#define _CPU
#include <cstdint>
#include <cstdio>
#include "control_unit.hpp"
#include "io.hpp"
#include "alu.hpp"
#include "registers.hpp"
#include "memory.hpp"


class CPU {
    private:
        int32_t bus_in, bus_out1, bus_out2;
        int32_t bus_pc, bus_inst; // Program Memory <=> Control unit
        int32_t pm_in;
        bool flag_z, flag_p, flag_n;
        ALU* alu;
        Registers* registers;
        Memory* data_memory;
        Memory* program_memory;
        Control_unit* control_unit;
        IO* io;

    public:
        CPU()
        {
            alu = new ALU(&bus_out1, &bus_out2, &bus_in, &flag_z, &flag_p,
                          &flag_n);
            registers = new Registers(&bus_in, &bus_out1, &bus_out2);
            data_memory = new Memory(&bus_out1, &bus_out2, &bus_in);
            program_memory = new Memory(&bus_pc, &pm_in, &bus_inst);
            io = new IO(&bus_in, &bus_out1, &bus_out2);
            control_unit = new Control_unit(&bus_pc, &bus_inst, &bus_out2,
                          &flag_z, &flag_p, &flag_n, alu, data_memory,
                          program_memory, registers, io);
        }

        void read_program (char* filename);
        
        Memory* getDataMemory() const
        { 
            return data_memory;
        }
        
        Control_unit* getControl_Unit() const
        {
            return control_unit;
        }
        
        IO* getIO() const
        {
            return io;
        }
        
        Registers* getRegisters() const
        {
            return registers;
        }
        
        ALU* getALU() const
        {
            return alu;
        }
        
};

#endif
