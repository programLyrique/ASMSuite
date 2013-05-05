/* 
 * File:   LabelBreakpoint.cpp
 * Author: pierre
 * 
 * Created on 6 mai 2013, 00:06
 */

#include "labelBreakpoint.hpp"

namespace debugger
{

    LabelBreakpoint::LabelBreakpoint(string label) : label(label)
    {
    }

    LabelBreakpoint::LabelBreakpoint(const LabelBreakpoint& orig)
    {
    }
    
    bool LabelBreakpoint::isBreak()
    {
        
    }

    LabelBreakpoint::~LabelBreakpoint()
    {
    }

}
