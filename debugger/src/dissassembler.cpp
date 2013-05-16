/* 
 * File:   Dissassembler.cpp
 * Author: pierre
 * 
 * Created on 12 mai 2013, 17:54
 */

#include "dissassembler.hpp"

using namespace std;

namespace debugger
{

/*
enum Instructions
    {
        ADD, ADDI, AND, ANDI, CALL, IN, JMP, JMR, JRE, JRS, LOAD, OR, ORI,
        OUT, RET, SL, SLI, SR, SRI, STORE, SUB, SUBI, XOR, XORI
    };
 */
Dissassembler::Dissassembler()
{
    //ALU
    instr["add"] = instructions::ADD;
    instr["addi"] = instructions::ADDI;
    instr["and"] = instructions::AND;
    instr["andi"] = instructions::ANDI;
    instr["sub"] = instructions::SUB;
    instr["subi"] = instructions::SUBI;
    instr["xor"] = instructions::XOR;
    instr["xori"] = instructions::XORI;
    instr["sl"] = instructions::SL;
    instr["sli"] = instructions::SLI;
    instr["sr"] = instructions::SR;
    instr["sri"] = instructions::SRI;
    instr["or"] = instructions::OR;
    instr["ori"] = instructions::ORI;
    //JMP inst
    instr["jmp"] = instructions::JMP;
    instr["jmr"] = instructions::JMR;
    instr["jre"] = instructions::JRE;
    instr["jrs"] = instructions::JRS;
    //Pas encore supportés, manifestement
    //instr["call"] = instructions::CALL;    
    //instr["ret"] = instructions::RET;
    
    //IO inst
    instr["in"] = instructions::IN;
    instr["out"] = instructions::OUT;
    //MEM inst
    instr["load"] = instructions::LOAD;
    instr["store"] = instructions::STORE;
}

inst_type::INST_TYPE Dissassembler::getInst_type(const std::string& inst) const 
{
    switch (instr.at(inst))
    {
    case instructions::ADD:
    case instructions::ADDI:
    case instructions::AND:
    case instructions::ANDI:
    case instructions::SUB:
    case instructions::SUBI:
    case instructions::XOR:
    case instructions::XORI:
    case instructions::SL:
    case instructions::SLI:
    case instructions::SR:
    case instructions::SRI:
    case instructions::OR:
    case instructions::ORI:
        return inst_type::ALU_INST;
        break;

    case instructions::CALL:
    case instructions::JMP:
    case instructions::JMR:;
    case instructions::JRE:
    case instructions::JRS:
    case instructions::RET:
        return inst_type::JMP_INST;
        break;
    case instructions::IN:
    case instructions::OUT:
        return inst_type::IO_INST;
        break;
    case instructions::LOAD:
    case instructions::STORE:
        return inst_type::MEM_INST;
        break;
    default://Ne devrait pas arriver
        throw out_of_range("Type d'instruction inconnue.");
        break;
    }
}

int Dissassembler::getOpcode(const std::string& inst) const
{

    //Pas de différenciation immédiat ou pas
    switch (instr.at(inst))
    {
        //ALU
    case instructions::ADD:
    case instructions::ADDI:
        return operation::ADD;

    case instructions::AND:
    case instructions::ANDI:
        return operation::AND;

    case instructions::SUB:
    case instructions::SUBI:
        return operation::SUB;

    case instructions::XOR:
    case instructions::XORI:
        return operation::XOR;

    case instructions::SL:
    case instructions::SLI:
        return operation::SL;
    case instructions::SR:
    case instructions::SRI:
        return operation::SR;
    case instructions::OR:
    case instructions::ORI:
        return operation::OR;

    //JMP
    case instructions::CALL://ne semble pas supporté par le simulateur
        return -1;
    case instructions::JMP:
        return JMP_I;
    case instructions::JMR:
        return -1; //ou lancer une exception ?
    case instructions::JRE:
        return JRE_I;
    case instructions::JRS:
        return JRS_I;
    case instructions::RET://Pas supporté par le compilateur ?
        return -1;
    
    //IO
    case instructions::IN:
        return io_op::IN;
    case instructions::OUT:
        return io_op::OUT;
        
    //MEM
    case instructions::LOAD:
        return mem_inst::LOAD;
    case instructions::STORE:
        return mem_inst::STORE;

    default://Ne devrait pas arriver
        throw out_of_range("Instruction inconnue");
        break;
    }
}

bool Dissassembler::isInst(const std::string& inst) const throw ()
{
    return instr.count(inst) > 0;
}

Dissassembler::~Dissassembler()
{
}

}
