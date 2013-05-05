/* 
 * File:   LineBreakPoint.hpp
 * Author: pierre
 *
 * Created on 5 mai 2013, 23:59
 */

#ifndef LINEBREAKPOINT_HPP
#define	LINEBREAKPOINT_HPP

#include "breakpoint.hpp"

namespace debugger
{

    /**
     * breakpoint sur une ligne (numéro => program counter)
     * @param pc
     */
    class LineBreakpoint : public Breakpoint
    {
    public:
        LineBreakpoint(int line);
        LineBreakpoint(const LineBreakpoint& orig);
        bool isBreak();
        virtual ~LineBreakpoint();
    private:
        int line;

    };

}

#endif	/* LINEBREAKPOINT_HPP */

