/* 
 * File:   InstrBreakpoint.hpp
 * Author: pierre
 *
 * Created on 6 mai 2013, 00:22
 */

#ifndef INSTRBREAKPOINT_HPP
#define	INSTRBREAKPOINT_HPP

#include "breakpoint.hpp"
#include <string>

namespace debugger
{

    class InstrBreakpoint : public Breakpoint
    {
    public:
        /**
         * \todo Utiliser l'enum des opcodes (ou define ) du simulateur
         */
        InstrBreakpoint(string instr);
        InstrBreakpoint(const InstrBreakpoint& orig);
        
        bool isBreak();
        virtual ~InstrBreakpoint();
    private:
        string instr;
    };

}

#endif	/* INSTRBREAKPOINT_HPP */

