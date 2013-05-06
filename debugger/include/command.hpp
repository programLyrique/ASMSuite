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
#include "adrBreakpoint.hpp"
#include "instrBreakpoint.hpp"
#include "labelBreakpoint.hpp"
#include "lineBreakPoint.hpp"

namespace debugger
{

    namespace command
    {

        enum Command
        {
            BREAKPOINT,
        };
    }
}

#endif	/* COMMAND_HPP */

