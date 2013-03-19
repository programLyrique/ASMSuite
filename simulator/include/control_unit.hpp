#ifndef _CONTROL_UNIT
#define _CONTROL_UNIT
#include <cstdint>
#include "alu.hpp"
#include "registers.hpp"
#include "memory.hpp"

#define D_N 65536
#define P_N 65536

#define ALU_INST 0
#define MEM_INST 1
#define IO_INST 2
#define JMP_INST 3

#define JMP 0
#define JRS 1
#define JRE 4

const int32_t mask_inst = 3;
const int32_t mask_op = 7;
const int32_t mask_im = 1;
const int32_t mask_reg = 31;
const int32_t mask_im_value = 65535;
const int32_t mask_addr_26 = 67108863; // 2^26 - 1
const int32_t mask_addr_11 = 2047;
class Control_unit {
    private:
        // linking with the program memory
        int32_t* pc;
        int32_t* inst;

        // immediate value (toward bus_in 2, for example)
        int32_t* imm_bus;

        // flags
        bool* flag_z;
        bool* flag_p;
        bool* flag_n;

        // Other component of the CPU commanded by the control unit.
        ALU* alu;
        Memory* data_memory;
        Memory* program_memory;
        Registers* registers;

        int32_t type_inst;
        int32_t op_code;
        int32_t im;
        int32_t r1, r2, r3;
        int32_t im_value;
        int32_t addr26, addr11;

        void read_inst ();
        void decode_inst ();
        void execute_inst ();
        void read_registers ();
        void jump_instruction ();
        void execute_ALU_op ();
        void execute_MEM_op ();
        void execute_IO_op ();
        void write_registers ();
    public:
        /*
         * Prerequisite : pc and inst are the addr and out field of the
         * program memory. imm_bus is one of the two "input" buses. The flag
         * as correctly linked to the ALU.
         */
        Control_unit (int32_t* _pc, int32_t* _inst, int32_t* _imm_bus,
                      bool* _flag_z, bool* _flag_p, bool* _flag_n,
                      ALU* _alu, Memory* _data_memory, 
                      Memory* _program_memory, Registers* _registers)
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

