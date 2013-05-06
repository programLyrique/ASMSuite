/* 
 * File:   AdrrBreakpoint.cpp
 * Author: pierre
 * 
 * Created on 6 mai 2013, 00:10
 */

#include "adrBreakpoint.hpp"

namespace debugger
{

    AdrBreakpoint::AdrBreakpoint(int adr, int offset) : adr(adr), offset(offset)
    {
    }

    AdrBreakpoint::AdrBreakpoint(const AdrBreakpoint& orig)
    {
    }

    bool AdrBreakpoint::isBreak()
    {
        return true;
    }
    
    AdrBreakpoint::~AdrBreakpoint()
    {
    }

}
