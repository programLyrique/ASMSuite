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
         * Breakpoint sur une adresse mémoire
         * @param orig
         */
        Breakpoint(int addr, int offset = 0);

        /**
         * Point d'arrêt sur un port I/O : quand il y a lecture ou écriture
         * Type 0 : in et out sur le port, 1 : in , 2 : out , 3 : in/out avec 
         * détection de valeur, 4 : in avec détection de valeur
         * 5 : out avec détection de valeur
         * @param port
         * @param type
         * @param val
         */
        Breakpoint(int port, int type = 0, int val = 0);

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

