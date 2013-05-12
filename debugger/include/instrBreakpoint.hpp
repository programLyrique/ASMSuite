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
#include <unordered_map>

namespace debugger
{

    class InstrBreakpoint : public Breakpoint
    {
    public:
        InstrBreakpoint(const Control_unit& cont, string instr);
        /**
         * Breakpoint on a opcode of a type of instruciton (mem, io, alu...)
         * @param type type of the instruction (\see control_unit.hpp)
         * @param opcode type of the opcode
         */
        InstrBreakpoint(const Control_unit& cont, inst_type::INST_TYPE type, int opcode);
        /**
         * Breakpoint on a type of instruction
         * @param type
         * @return 
         */
        InstrBreakpoint(const Control_unit& cont, inst_type::INST_TYPE type);
        InstrBreakpoint(const InstrBreakpoint& orig);
        
        bool isBreak();
        virtual ~InstrBreakpoint();
    private:
        const Control_unit& cont;
        inst_type::INST_TYPE type;
        int opcode;
        bool ignoreOpcode;
    };

}

#endif	/* INSTRBREAKPOINT_HPP */

