/* 
 * File:   LineBreakPoint.hpp
 * Author: pierre
 *
 * Created on 5 mai 2013, 23:59
 */

#ifndef LINEBREAKPOINT_HPP
#define	LINEBREAKPOINT_HPP

#include "breakpoint.hpp"
#include "cpu.hpp"

namespace debugger
{

    /**
     * breakpoint sur une ligne (numéro => program counter)
     * @param pc
     */
    class LineBreakpoint : public Breakpoint
    {
    public:
        LineBreakpoint(CPU* cpu, int line);
        LineBreakpoint(const LineBreakpoint& orig);
        bool isBreak();
        string describe();
        virtual ~LineBreakpoint();
    private:
        int line;
        CPU* cpu;

    };

}

#endif	/* LINEBREAKPOINT_HPP */

