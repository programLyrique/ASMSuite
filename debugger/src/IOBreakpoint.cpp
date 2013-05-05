/* 
 * File:   IOBreakpoint.cpp
 * Author: pierre
 * 
 * Created on 6 mai 2013, 00:16
 */

#include "IOBreakpoint.hpp"

namespace debugger
{

    IOBreakpoint::IOBreakpoint(int port, IOBreakpoint::Type type, int val) : port(port), type(type), val(val)
    {
    }

    IOBreakpoint::IOBreakpoint(const IOBreakpoint& orig)
    {
    }
    
    bool IOBreakpoint::isBreak()
    {
        
    }

    IOBreakpoint::~IOBreakpoint()
    {
    }

}

