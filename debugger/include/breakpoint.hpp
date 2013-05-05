/* 
 * File:   breakpoint.hpp
 * Author: pierre
 *
 * Created on 5 mai 2013, 22:18
 */

#ifndef BREAKPOINT_HPP
#define	BREAKPOINT_HPP

#include <string>

using namespace std;

namespace debugger
{

    class Breakpoint
    {
    public:
        
        /**
         * Renvoie vrai s'il faut s'arrêter
         * @return 
         */
        virtual bool isBreak() = 0;

        virtual ~Breakpoint(){}
    private:

    };

}

#endif	/* BREAKPOINT_H */

