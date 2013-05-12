/* 
 * File:   InstrBreakpoint.cpp
 * Author: pierre
 * 
 * Created on 6 mai 2013, 00:22
 */

#include "instrBreakpoint.hpp"

namespace debugger
{

    InstrBreakpoint::InstrBreakpoint(const Control_unit& cont, string instr) :
    cont(cont)
    {
    }
    
    InstrBreakpoint::InstrBreakpoint(const Control_unit& cont, inst_type::INST_TYPE type) : 
        cont(cont), type(type), opcode(-1), ignoreOpcode(true)
    {
        
    }
    
    InstrBreakpoint::InstrBreakpoint(const Control_unit& cont, inst_type::INST_TYPE type, int opcode) : 
        cont(cont), type(type), opcode(opcode), ignoreOpcode(false)
    {
        
    }

    bool InstrBreakpoint::isBreak()
    {
        return cont.getInst_type() == type && (ignoreOpcode || cont.getOpcode() == opcode);
    }

    InstrBreakpoint::~InstrBreakpoint()
    {
    }

}

