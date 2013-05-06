/* 
 * File:   InstrBreakpoint.cpp
 * Author: pierre
 * 
 * Created on 6 mai 2013, 00:22
 */

#include "instrBreakpoint.hpp"

namespace debugger
{

    InstrBreakpoint::InstrBreakpoint(string instr) : instr(instr)
    {
    }

    bool InstrBreakpoint::isBreak()
    {
        return true;
    }

    InstrBreakpoint::InstrBreakpoint(const InstrBreakpoint& orig)
    {
    }

    InstrBreakpoint::~InstrBreakpoint()
    {
    }

}

