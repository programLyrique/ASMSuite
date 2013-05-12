/* 
 * File:   LineBreakPoint.cpp
 * Author: pierre
 * 
 * Created on 5 mai 2013, 23:59
 */

#include "lineBreakPoint.hpp"

#include <iostream>

namespace debugger
{

    LineBreakpoint::LineBreakpoint(CPU* cpu, int line) : cpu(cpu), line(line)
    {
    }

    LineBreakpoint::LineBreakpoint(const LineBreakpoint& orig)
    {
    }

    bool LineBreakpoint::isBreak()
    {
        return cpu->getBus_pc() == static_cast<int32_t>(line);
    }
    
    string LineBreakpoint::describe()
    {
        ostringstream out;
        out << "Line " << line;
        return out.str();
    }
    
    LineBreakpoint::~LineBreakpoint()
    {
    }

}

