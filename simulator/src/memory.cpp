#include "memory.hpp"

template <int N>
Memory<N>::Memory(int32_t* _addr, int32_t* _in, int32_t* _out)
{
    addr = _addr;
    in = _in;
    out = _out;
}

template <int N>
void Memory<N>::load ()
{
    *out = memory[*addr];
}

template <int N>
void Memory<N>::store ()
{
    memory[*addr] = *in;
}

