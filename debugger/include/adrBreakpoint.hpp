/* 
 * File:   AdrrBreakpoint.hpp
 * Author: pierre
 *
 * Created on 6 mai 2013, 00:10
 */

#ifndef ADRRBREAKPOINT_HPP
#define	ADRRBREAKPOINT_HPP

#include "breakpoint.hpp"


namespace debugger
{

    /**
     * Breakpoint sur une adresse mémoire
     * @param orig
     */
    class AdrBreakpoint : public Breakpoint
    {
    public:
        AdrBreakpoint(int addr, int offset);
        AdrBreakpoint(const AdrBreakpoint& orig);
        bool isBreak();
        virtual ~AdrBreakpoint();
    private:
        int adr;
        int offset;
    };

}

#endif	/* ADRRBREAKPOINT_HPP */

