/* 
 * File:   Dissassembler.hpp
 * Author: pierre
 *
 * Created on 12 mai 2013, 17:54
 */

#ifndef DISSASSEMBLER_HPP
#define	DISSASSEMBLER_HPP

#include <unordered_map>
#include <string>
#include <stdexcept>

#include "control_unit.hpp"

namespace debugger
{

namespace instructions
{
    enum Instructions
    {
        ADD, ADDI, AND, ANDI, CALL, IN, JMP, JMR, JRE, JRS, LOAD, OR, ORI,
        OUT, RET, SL, SLI, SR, SRI, STORE, SUB, SUBI, XOR, XORI
    };
}
/**
 * Pour avoir les correspondances instructions -> type d'instruction et opcode
 * Surtout utilisé pour le point d'arrêt sur instructions
 * Il n'y a besoin d'en créer qu'un seul pour le debugger, bien sûr
 */
class Dissassembler
{
public:
    Dissassembler();

    inst_type::INST_TYPE getInst_type(const std::string& inst) const;

    int getOpcode(const std::string& inst) const;

    bool isInst(const std::string& inst) const throw ();

    virtual ~Dissassembler();

private:

    std::unordered_map<std::string, instructions::Instructions> instr;
};

}

#endif	/* DISSASSEMBLER_HPP */

