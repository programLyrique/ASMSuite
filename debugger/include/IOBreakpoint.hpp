/* 
 * File:   IOBreakpoint.hpp
 * Author: pierre
 *
 * Created on 6 mai 2013, 00:16
 */

#ifndef IOBREAKPOINT_HPP
#define	IOBREAKPOINT_HPP

#include "breakpoint.hpp"


namespace debugger
{

    /**
     * Point d'arrêt sur un port I/O : quand il y a lecture ou écriture
     * Type 0 : in et out sur le port, 1 : in , 2 : out , 3 : in/out avec 
     * détection de valeur, 4 : in avec détection de valeur
     * 5 : out avec détection de valeur
     * @param port
     * @param type
     * @param val
     */
    class IOBreakpoint : public Breakpoint
    {
    public:
        IOBreakpoint(int port, Type type = IO, int val = 0);
        IOBreakpoint(const IOBreakpoint& orig);
        bool isBreak();
        virtual ~IOBreakpoint();

        enum Type
        {
            IO,
            IN,
            OUT,
            IOVAl,
            INVAL,
            OUTVAL
        };
    private:
        int port;
        Type type;
        int val;

    };

}

#endif	/* IOBREAKPOINT_HPP */

