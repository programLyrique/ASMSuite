/* 
 * File:   LabelBreakpoint.hpp
 * Author: pierre
 *
 * Created on 6 mai 2013, 00:06
 */

#ifndef LABELBREAKPOINT_HPP
#define	LABELBREAKPOINT_HPP

#include "breakpoint.hpp"
#include <string>


namespace debugger
{

    class LabelBreakpoint : public Breakpoint
    {
    public:
        LabelBreakpoint(string label);
        LabelBreakpoint(const LabelBreakpoint& orig);
        bool isBreak();
        virtual ~LabelBreakpoint();
    private:
        string label;
    };

}

#endif	/* LABELBREAKPOINT_HPP */

