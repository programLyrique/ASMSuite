#include "debugger.hpp"
#include <iostream>

namespace debugger
{

    Debugger::Debugger(CommandInterface& inter) : interf(inter)
    {
        /*
         * Initialisation des correspondances de sous-commandes pour les points d'arrêt
         */
        break_commands["line"] = breakpoint::LINE;
        break_commands["label"] = breakpoint::LABEL;
        break_commands["port"] = breakpoint::PORT;
        break_commands["instr"] = breakpoint::INSTR;
        break_commands["adr"] = breakpoint::ADR;
        
        //Pour tester 
        breakpoints.push_back(new InstrBreakpoint("salut"));

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


            //Déclaration pour les variables du switch (plutôt que d'utiliser -fpermissive)
            Breakpoint * breakpoint; //pourtant locale...

//            for(int i = 0; i < args.size(); i++)     
//            {
//                cout << args[i] << " " ;
//            }
//            cout << endl;
            
            switch (command) {
            case command::BREAKPOINT:
                if (addBreakpoint(args) != nullptr) {
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

    Breakpoint* Debugger::addBreakpoint(const vector<string>& args)
    {
        int nbArgs = args.size();
        //le premier argument correspond au type de breakpoint

        Breakpoint* breakpoint = nullptr;

        if (nbArgs == 0) {
            interf.errorMessage("Pas de sous commande pour le point d'arrêt");
            return breakpoint;
        }

        nbArgs--; //On a traité le premier argument

        breakpoint::Breakpoint_t sub_command;
        
        try {
            sub_command = break_commands.at(args[0]);
        }
        catch (const out_of_range& e) {
            interf.errorMessage("Sous-commande de point d'arrêt inconnue");
            return breakpoint;
        }

        try {

            switch (sub_command) {
            case breakpoint::LINE:
                //L'argument suivant est une ligne
                breakpoint = new LineBreakpoint(stoi(args[1]));
                break;
            case breakpoint::LABEL:
                breakpoint = new LabelBreakpoint(args[1]);
                break;
            case breakpoint::PORT:
                if (nbArgs == 1) {
                    breakpoint = new IOBreakpoint(stoi(args[1]));
                }
                else if (nbArgs == 2) {
                    breakpoint = new IOBreakpoint(stoi(args[1]), static_cast<io_breakpoint::Type> (stoi(args[2])));
                }
                else if (nbArgs == 3) {
                    breakpoint = new IOBreakpoint(stoi(args[1]), static_cast<io_breakpoint::Type> (stoi(args[2])),
                                                  stoi(args[3]));
                }
                else {
                    stringstream ss;
                    ss << nbArgs;
                    throw out_of_range(ss.str());
                }
                break;
            case breakpoint::INSTR:
                breakpoint = new InstrBreakpoint(args[1]);
                break;
            case breakpoint::ADR:
                if (nbArgs == 1) {
                    int adr = stoi(args[1]);
                    breakpoint = new AdrBreakpoint(adr, adr);

                }
                else if (nbArgs == 2) {
                    breakpoint = new AdrBreakpoint(stoi(args[1]), stoi(args[2]));
                }
                else {
                    stringstream ss;
                    ss << nbArgs;
                    throw out_of_range(ss.str());
                }
                break;
            default://Ne devrait pas arriver car plutôt levée d'une exception
                interf.errorMessage("Sous-commande de point d'arrêt inconnue");
                break;
            }
        }
        catch (const out_of_range& e) {
            interf.errorMessage(string("Mauvais nombre d'arguments : ") + e.what());
        }
        catch (const exception& e) {
            interf.errorMessage("Mauvais arguments");
        }
        return breakpoint;
    }

    Debugger::~Debugger()
    {
        //vector désalloue tout-seul
        /*
         for (int i = 0; i < breakpoints.size(); i++) {
            delete breakpoints[i];
        }
         */
    }

}
