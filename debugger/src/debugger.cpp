#include "debugger.hpp"

namespace debugger
{

    Debugger::Debugger(CommandInterface& inter) : interf(inter)
    {

    }

    bool Debugger::interact()
    {
        //Point d'arrêt ?
        bool breaks;
        for (int i = 0; i < breakpoints.size(); i++) {
            if (breakpoints[i]->isBreak()) {
                breaks = true;
                break;
            }
        }
        if (breaks) {
            vector<string> args;
            //On affiche l'invite pour rentrer une commande de debogage
            command::Command command = interf.prompt(args);
            
            //Supprimer le premier élément (qui  est le nom de la commande)
            args.erase(args.begin());
            
            //Déclaration pour les variables du switch (plutôt que d'utiliser -fpermissive)
            Breakpoint * breakpoint;//pourtant locale...
            
            switch (command) {
            case command::BREAKPOINT:           
                if(addBreakpoint(args) != nullptr)
                {
                    breakpoints.push_back(breakpoint);
                }
                //addBreakpoint se charge d'indiquer les erreurs
            
                break;

            default:
                interf.errorMessage("Impossible de détecter la commande.");
                break;
            }
        }
    }
    
    Breakpoint* Debugger::addBreakpoint(vector<string> args)
    {
        int nbArgs = args.size();
    }

}
