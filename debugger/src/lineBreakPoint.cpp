/* 
 * File:   LineBreakPoint.cpp
 * Author: pierre
 * 
 * Created on 5 mai 2013, 23:59
 */

#include "lineBreakPoint.hpp"


namespace debugger
{

    LineBreakpoint::LineBreakpoint(int line) : line(line)
    {
    }

    LineBreakpoint::LineBreakpoint(const LineBreakpoint& orig)
    {
    }

    bool LineBreakpoint::isBreak()
    {
        
    }
    
    LineBreakpoint::~LineBreakpoint()
    {
    }

}

