/* 
 * File:   command.hpp
 * Author: pierre
 *
 * Created on 6 mai 2013, 14:40
 */

#ifndef COMMAND_HPP
#define	COMMAND_HPP

//Quelques includes utiles

#include "IOBreakpoint.hpp"
#include "instrBreakpoint.hpp"
#include "adrBreakpoint.hpp"
#include "labelBreakpoint.hpp"
#include "lineBreakPoint.hpp"

namespace debugger
{

namespace command
{

enum Command
{
    BREAKPOINT,
    SEARCH,
    SEARCH_NEXT,
    DISPLAY,
    DUMP,
    PRINT,
    WRITE,
    ERROR,
    RUN,
    NEXT,
    STEP,
    HELP,
    INFO,
    CLEAR,
    EXIT
};
}
}

#endif	/* COMMAND_HPP */

