#include "alu.hpp"
ALU::ALU(int32_t* _in1, int32_t* _in2, int32_t* _out, bool* _flag_z,
         bool* _flag_p, bool* _flag_n)
{
    in1 = _in1;
    in2 = _in2;
    out = _out;
    flag_z = _flag_z;
    flag_p = _flag_p;
    flag_n = _flag_n;
}

void ALU::do_add ()
{
    *out = *in1 + *in2;
}

void ALU::do_sub ()
{
    *out = *in1 - *in2;
}

void ALU::do_and ()
{
    *out = *in1 & *in2;
}

void ALU::do_or ()
{
    *out = *in1 | *in2;
}

void ALU::do_xor ()
{
    *out = *in1 ^ *in2;
}

void ALU::do_sr ()
{
    *out = *in1 >> *in2;
}

void ALU::do_sl ()
{
    *out = *in1 << *in2;
}

void ALU::do_op (int op)
{
    switch (op) {
        case ADD: do_add(); break;
        case SUB: do_sub(); break;
        case AND: do_and(); break;
        case OR: do_or(); break;
        case XOR: do_xor(); break;
        case SR: do_sr(); break;
        case SL: do_sl(); break;
        default: ;
    }
    *out == 0 ? *flag_z = 1 : *flag_z = 0;
    *out >= 0 ? *flag_p = 1 : *flag_p = 0;
    *out <= 0 ? *flag_n = 1 : *flag_n = 0;
}

