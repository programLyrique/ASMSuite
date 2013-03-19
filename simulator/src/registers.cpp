#include "registers.hpp"

Registers::Registers(int32_t* _in, int32_t* _out1, int32_t* _out2)
{
    in = _in;
    out1 = _out1;
    out2 = _out2;
}

void Registers::read (int reg_out1, int reg_out2)
{
    *out1 = registers[reg_out1];
    *out2 = registers[reg_out2];
}

void Registers::write (int reg_in)
{
    registers[reg_in] = *in;
}

