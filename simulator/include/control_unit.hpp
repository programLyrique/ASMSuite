#ifndef _CONTROL_UNIT
#define _CONTROL_UNIT
#include <cstdint>
#include "alu.hpp"
#include "registers.hpp"
#include "memory.hpp"
class Control_unit {
    private:
        // linking with the program memory
        int32_t* pc;
        int32_t* inst;

        // immediate value (toward bus_in 2, for example)
        int32_t* imm_bus;

        // flags
        int32_t* flag_z;
        int32_t* flag_p;
        int32_t* flag_n;

        // Other component of the CPU commanded by the control unit.
        ALU* alu;
        Memory* data_memory;
        Memory* program_memory;
        Registers* registers;

        int type_inst;
        int op_code;
        bool im;
        int r1, r2, r3;
        int addr26, addr11;

    public:
        Control_unit (int32_t* _pc, int32_t* _inst, int32_t* _imm_bus,
                      int32_t* _flag_z, int32_t* _flag_p, int32_t* _flag_n,
                      ALU* _alu, Memory* _data_memory; Memory* _program_memory,
                      Registers* _registers)
        {
            pc = _pc;
            inst = _inst;
            imm_bus = _imm_bus;
            flag_z = _flag_z;
            flag_p = _flag_p;
            flag_n = _flag_n;
            alu = _alu;
            data_memory = _data_memory;
            program_memory = _program_memory;
            registers = _registers;
        }
};
#endif

