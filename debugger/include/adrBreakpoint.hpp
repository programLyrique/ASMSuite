/* 
 * File:   AdrrBreakpoint.hpp
 * Author: pierre
 *
 * Created on 6 mai 2013, 00:10
 */

#ifndef ADRRBREAKPOINT_HPP
#define	ADRRBREAKPOINT_HPP

#include "instrBreakpoint.hpp"
#include "cpu.hpp"

namespace debugger
{

    /**
     * Breakpoint sur une adresse mémoire
     * @param orig
     */
    class AdrBreakpoint : public InstrBreakpoint
    {
    public:
        AdrBreakpoint(const CPU& cpu,int addr, int offset);
        bool isBreak();
        virtual ~AdrBreakpoint();
    private:
        int addr;
        int offset;
        const CPU& cpu;
    };

}

#endif	/* ADRRBREAKPOINT_HPP */

