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
    for(int i = 0; i < breakpoints.size() ; i++)
    {
        if(breakpoints[i].isBreak())
        {
            breaks = true;
            break;
        }
    }
    if(breaks)
    {
        //On affiche l'invite pour rentrer une commande de debogage
        interf.prompt();
    }
}

}
