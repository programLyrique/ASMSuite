/* 
 * File:   AdrrBreakpoint.cpp
 * Author: pierre
 * 
 * Created on 6 mai 2013, 00:10
 */

#include "instrBreakpoint.hpp"
#include "adrBreakpoint.hpp"

namespace debugger
{

    AdrBreakpoint::AdrBreakpoint(const CPU& cpu, int addr, int offset) : 
        InstrBreakpoint(*(cpu.getControl_unit()), inst_type::MEM_INST),
        cpu(cpu), addr(addr), offset(offset)
    {
    }


    bool AdrBreakpoint::isBreak()
    {
        //Si oui, on regarde les addresse en question
        if(InstrBreakpoint::isBreak())
        {
            int address = cpu.getBus_out1();
            return address >= addr && address < addr+offset;
        }
        return false;
    }
    
    string AdrBreakpoint::describe()
    {
        ostringstream out;
        out << "MEM[" << addr << "..." << (addr+ offset) << "[";
        return out.str();
    }
    
    AdrBreakpoint::~AdrBreakpoint()
    {
    }

}
