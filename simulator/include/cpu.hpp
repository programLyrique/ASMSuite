#ifndef _CPU
#define _CPU
#include <cstdint>
#include <cstdio>
#include "control_unit.hpp"
#include "io.hpp"
#include "alu.hpp"
#include "registers.hpp"
#include "memory.hpp"

class CPU
{
private:
    int32_t bus_in, bus_out1, bus_out2;
    int32_t bus_pc, bus_inst; // Program Memory <=> Control unit
    int32_t pm_in; // pour lire le programme.
    bool flag_z, flag_p, flag_n; // mais les flags ne servent à rien...
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

    void read_program(char* filename);

    void run(); // exécute le programme

    void run_debug(); //Exécute le programme en mode debug

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

    ALU* getAlu() const
    {
        return alu;
    }

    void setAlu(ALU* alu)
    {
        this->alu = alu;
    }

    int32_t getBus_in() const
    {
        return bus_in;
    }

    void setBus_in(int32_t bus_in)
    {
        this->bus_in = bus_in;
    }

    int32_t getBus_inst() const
    {
        return bus_inst;
    }

    void setBus_inst(int32_t bus_inst)
    {
        this->bus_inst = bus_inst;
    }

    int32_t getBus_out1() const
    {
        return bus_out1;
    }

    void setBus_out1(int32_t bus_out1)
    {
        this->bus_out1 = bus_out1;
    }

    int32_t getBus_out2() const
    {
        return bus_out2;
    }

    void setBus_out2(int32_t bus_out2)
    {
        this->bus_out2 = bus_out2;
    }

    int32_t getBus_pc() const
    {
        return bus_pc;
    }

    void setBus_pc(int32_t bus_pc)
    {
        this->bus_pc = bus_pc;
    }

    Control_unit* getControl_unit() const
    {
        return control_unit;
    }

    void setControl_unit(Control_unit* control_unit)
    {
        this->control_unit = control_unit;
    }

    Memory* getData_memory() const
    {
        return data_memory;
    }

    void setData_memory(Memory* data_memory)
    {
        this->data_memory = data_memory;
    }

    bool isFlag_n() const
    {
        return flag_n;
    }

    void setFlag_n(bool flag_n)
    {
        this->flag_n = flag_n;
    }

    bool isFlag_p() const
    {
        return flag_p;
    }

    void setFlag_p(bool flag_p)
    {
        this->flag_p = flag_p;
    }

    bool isFlag_z() const
    {
        return flag_z;
    }

    void setFlag_z(bool flag_z)
    {
        this->flag_z = flag_z;
    }

    IO* getIo() const
    {
        return io;
    }

    void setIo(IO* io)
    {
        this->io = io;
    }

    int32_t getPm_in() const
    {
        return pm_in;
    }

    void setPm_in(int32_t pm_in)
    {
        this->pm_in = pm_in;
    }

    Memory* getProgram_memory() const
    {
        return program_memory;
    }

    void setProgram_memory(Memory* program_memory)
    {
        this->program_memory = program_memory;
    }


};

#endif
