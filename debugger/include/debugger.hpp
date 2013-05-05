#ifndef DEBUGGER_H
#define DEBUGGER_H

#include "commandInterface.hpp"

namespace debugger
{

//enum
//{
//
//};


class Simulator;

/**
 * La classe en charge de la gestion du debogage.
 *
 * Il faut « attacher » un debugger à un simulateur via la méthode
 * attach du simulateur.
 */
class Debugger
{
    private:

    Simulator* sim;

    CommandInterface& interf;

    public:
    /**
     *
     */
    Debugger(CommandInterface& inter);

    /**
     * Cette méthode est appelée par la fonction attach de Simulator.
     */
//    void registerSimulator(Simulator* s)
//    {
//        sim = s;
//    }

    /**
     * Dans la boucle principale du simulateur. Stoppe l'exécution, affiche les
     * informations demandées, inspecte le simulateur.
     * @return false si le simulateur doit être arrêté.
     */
    bool interact();

    virtual ~Debugger(){}
};

}

#endif
