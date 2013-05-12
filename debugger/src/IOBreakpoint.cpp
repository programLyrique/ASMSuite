/* 
 * File:   IOBreakpoint.cpp
 * Author: pierre
 * 
 * Created on 6 mai 2013, 00:16
 */

#include "IOBreakpoint.hpp"

namespace debugger
{

    IOBreakpoint::IOBreakpoint(int port, io_breakpoint::Type type, int val) : port(port), type(type), val(val)
    {
    }

    IOBreakpoint::IOBreakpoint(const IOBreakpoint& orig)
    {
    }
    
    bool IOBreakpoint::isBreak()
    {
        return true;
    }
    
    string IOBreakpoint::describe()
    {
        ostringstream out;
        out << "IO port = " << port << " type  = " << type << " val = " << val;
        return out.str();
    }

    IOBreakpoint::~IOBreakpoint()
    {
    }

}

