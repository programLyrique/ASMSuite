#include "memory.hpp"

Memory::Memory(int32_t* _addr, int32_t* _in, int32_t* _out)
{
    addr = _addr;
    in = _in;
    out = _out;
}

void Memory::load ()
{
    *out = memory[*addr];
}

void Memory::store ()
{
    memory[*addr] = *in;
}

