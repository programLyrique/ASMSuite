/* 
 * File:   breakpoint.hpp
 * Author: pierre
 *
 * Created on 5 mai 2013, 22:18
 */

#ifndef BREAKPOINT_HPP
#define	BREAKPOINT_HPP

#include <string>
#include <sstream>
#include "control_unit.hpp"

class CPU;//en attendant l'include du simulateur

using namespace std;

namespace debugger
{

    namespace breakpoint
    {
        enum Breakpoint_t
        {
            LINE,
            LABEL,
            INSTR,
            PORT,
            ADR
        };
    }
    class Breakpoint
    {
    public:
        
        /**
         * Renvoie vrai s'il faut s'arrêter
         * @return 
         */
        virtual bool isBreak() = 0;
        
        /**
         * Describes the breakpoint
         * @return 
         */
        virtual string describe() = 0;

        virtual ~Breakpoint() {};
    };

}

#endif	/* BREAKPOINT_H */

