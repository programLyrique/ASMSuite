#include "control_unit.hpp"

#include <iostream>

void Control_unit::read_inst()
{
    program_memory -> load();
}

void Control_unit::decode_inst()
{
    type_inst = (*inst >> 30) & mask_inst;
    op_code = (*inst >> 27) & mask_op;
    im = (*inst >> 26) & mask_im;
    r1 = (*inst >> 21) & mask_reg;
    r2 = (*inst >> 16) & mask_reg;
    r3 = (*inst >> 11) & mask_reg;
    im_value = (*inst) & mask_im_value;
    addr26 = (*inst) & mask_addr_26;
    addr11 = (*inst) & mask_addr_11;
}

void Control_unit::execute_inst()
{
    switch (type_inst)
    {
    case inst_type::ALU_INST: read_registers();
        execute_ALU_op();
        write_registers();
        (*pc)++;
        break;
    case inst_type::MEM_INST: read_registers();
        execute_MEM_op();
        write_registers();
        (*pc)++;
        break;
    case inst_type::IO_INST:
        read_registers();
        execute_IO_op();
        write_registers();
        (*pc)++;
        break;
    case inst_type::JMP_INST: jump_instruction();
        break;
    default:
        std::cerr << "Erreur fatale" << std::endl;
        exit(1);

    }
}

void Control_unit::read_registers()
{
    registers -> read(r2, r3);
}

void Control_unit::write_registers()
{
    registers -> write(r1);
}

void Control_unit::execute_ALU_op()
{
    if (im)
    {
        *imm_bus = im_value;
    }
    alu -> do_op(op_code);
}

void Control_unit::execute_MEM_op()
{
    switch (op_code)
    {
    case mem_inst::LOAD: data_memory -> load();
        break;
    case mem_inst::STORE: data_memory -> store();
        break;
    default:;
    }
}

void Control_unit::execute_IO_op()
{
    switch (op_code)
    {
    case io_op::IN: io -> input();
        break;
    case io_op::OUT: io -> output();
        break;
    default:;
    }
}

void Control_unit::jump_instruction()
{
    if (op_code == JMP)
    {
        r1 = 0;
        r2 = 0;
        r3 = 0;
        im = 1;
        im_value = 0;
        read_registers();
        execute_ALU_op();
        *pc = addr26;
    }
    else
    {
        read_registers();
        execute_ALU_op();
        if ((op_code == JRS && *flag_p) || (op_code == JRE && *flag_z))
        {
            *pc += addr11;
        }
        else
        {
            (*pc)++;
        }
    }
}

void Control_unit::execute_program() // truc de guedin...
{
    while (*inst != -1)
    {
        read_inst();
        decode_inst();
        execute_inst();
    }
}
