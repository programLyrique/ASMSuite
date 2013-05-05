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
         * Point d'arrêt à chaque fois qu'on rencontre une telle instruction.
         * Par exemple, à chaque fois qu'on détecte une instruction add
         * @param instructions
         */
        Breakpoint(string instructions);


        /**
         * Copie d'un breakpoint
         * @param orig
         */
        Breakpoint(const Breakpoint& orig);
        
        /**
         * Renvoie vrai s'il faut s'arrêter
         * @return 
         */
        virtual bool isBreak() = 0;

        virtual ~Breakpoint();
    private:

    };

}

#endif	/* BREAKPOINT_H */

