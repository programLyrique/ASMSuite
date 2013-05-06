#ifndef DEBUGGER_H
#define DEBUGGER_H


#include <vector>
#include <unordered_map>
#include <stdexcept>   
#include <sstream>

#include "command.hpp"
#include "commandInterface.hpp"
#include "breakpoint.hpp"

namespace debugger
{


    class CPU;

    /**
     * La classe en charge de la gestion du debogage.
     *
     * Il faut « attacher » un debugger à un simulateur via la méthode
     * attach du simulateur.
     * \todo laisser charger un fichier qui contienne des commandes pour le debugger
     * à exécuter à chaque breakpoint
     */
    class Debugger
    {
    private:

        CPU* sim;

        CommandInterface& interf;

        vector<Breakpoint*> breakpoints;
        
        unordered_map<string, breakpoint::Breakpoint_t> break_commands;
        
        /**
         * Etudie les arguments pour créer le bon type de breakpoints
         * @param args
         * @return null if the breakpoint is invalid
         */
        Breakpoint* addBreakpoint(const vector<string>& args);

    public:
        /**
         *
         */
        Debugger(CommandInterface& inter);

        /**
         * Cette méthode est appelée par la fonction attach de Simulator.
         */
            void registerSimulator(CPU* s)
            {
                sim = s;
            }

        /**
         * Dans la boucle principale du simulateur. Stoppe l'exécution, affiche les
         * informations demandées, inspecte le simulateur.
         * @return false si le simulateur doit être arrêté.
         */
        bool interact();

        virtual ~Debugger();

    };

}

#endif
