#include "debugger.hpp"
#include <iostream>

using namespace std;

namespace debugger
{

Debugger::Debugger(CommandInterface& inter) : interf(inter), errMess(inter)
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
    for (int i = 0; i < breakpoints.size(); i++)
    {
        if (breakpoints[i]->isBreak())
        {
            breaks = true;
            break;
        }
    }
    if (breaks)
    {
        vector<string> args;
        //On affiche l'invite pour rentrer une commande de debogage
        command::Command command = interf.prompt(args);


        //Déclaration pour les variables du switch (plutôt que d'utiliser -fpermissive)
        Breakpoint * breakpoint; //pourtant locale...
        ostringstream out;
        switch (command)
        {
        case command::BREAKPOINT:
            if (addBreakpoint(args) != nullptr)
            {
                breakpoints.push_back(breakpoint);
            }
            //addBreakpoint se charge d'indiquer les erreurs

            break;
        case command::DISPLAY:
            display(args);
            break;
        case command::PRINT:
            for (int i = 0; i < args.size(); i++)
            {
                out << args[i] << " ";
            }
            interf.answer(out);

            break;
        case command::DUMP:
            dum(args);
            break;
        case command::SEARCH:
            break;
        case command::SEARCH_NEXT:
            break;
        default:
            errMess.unknownCommand();
            break;
        }
    }
}

Breakpoint* Debugger::addBreakpoint(const vector<string>& args)
{
    int nbArgs = args.size();
    //le premier argument correspond au type de breakpoint

    Breakpoint* breakpoint = nullptr;

    if (nbArgs == 0)
    {
        errMess.noSubCommand();
        return breakpoint;
    }

    nbArgs--; //On a traité le premier argument

    breakpoint::Breakpoint_t sub_command;

    try
    {
        sub_command = break_commands.at(args[0]);
    }
    catch (const out_of_range& e)
    {
        errMess.unknownSubCommand();
        return breakpoint;
    }

    try
    {

        switch (sub_command)
        {
        case breakpoint::LINE:
            //L'argument suivant est une ligne
            breakpoint = new LineBreakpoint(stoi(args[1]));
            break;
        case breakpoint::LABEL:
            breakpoint = new LabelBreakpoint(args[1]);
            break;
        case breakpoint::PORT:
            if (nbArgs == 1)
            {
                breakpoint = new IOBreakpoint(stoi(args[1]));
            }
            else if (nbArgs == 2)
            {
                breakpoint = new IOBreakpoint(stoi(args[1]), static_cast<io_breakpoint::Type> (stoi(args[2])));
            }
            else if (nbArgs == 3)
            {
                breakpoint = new IOBreakpoint(stoi(args[1]), static_cast<io_breakpoint::Type> (stoi(args[2])),
                                              stoi(args[3]));
            }
            else
            {
                stringstream ss;
                ss << nbArgs;
                throw out_of_range(ss.str());
            }
            break;
        case breakpoint::INSTR:
            breakpoint = new InstrBreakpoint(args[1]);
            break;
        case breakpoint::ADR:
            if (nbArgs == 1)
            {
                int adr = stoi(args[1]);
                breakpoint = new AdrBreakpoint(adr, adr);

            }
            else if (nbArgs == 2)
            {
                breakpoint = new AdrBreakpoint(stoi(args[1]), stoi(args[2]));
            }
            else
            {
                stringstream ss;
                ss << nbArgs;
                throw out_of_range(ss.str());
            }
            break;
        default://Ne devrait pas arriver car plutôt levée d'une exception
            errMess.unknownSubCommand();
            break;
        }
    }
    catch (const out_of_range& e)
    {
        errMess.badNumberArgs();
    }
    catch (const exception& e)
    {
        errMess.badArgs();
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

void Debugger::displayRegister(int i)
{
    ostringstream out;
    out << "REG[" << i << "] = "; //rajouter la bonne valeur
    interf.answer(out);
}

void Debugger::displayRegisters()
{
    ostringstream out;
    int nbRegistres = 4;
    for (int i = 1; i <= nbRegistres; i += 2)
    {
        out << "REG[" << i << "] = " << "\t REG[" << (i + 1) << "] = " << endl;
    }
    interf.answer(out);
}

void Debugger::displayAddress(int addr)
{
    ostringstream out;
    out << "MEM[" << addr << "] = ";
    interf.answer(out);
}

void Debugger::displayAdress(int addr, int offset)
{
    ostringstream out;
    //out << 
}

void Debugger::dumpMem(int addr, int offset, const string& fileName)
{
    //ostream file(fileName);

    interf.answer("Sauvegarde de la plage mémoire dans le fichier.");

}

bool Debugger::display(const vector<string>& args)
{
    int nbArgs = args.size();
    if (nbArgs == 0)
    {
        errMess.noSubCommand();
        return false;
    }

    nbArgs--;

    try
    {
        if (args[0] == "register")
        {
            if (nbArgs == 0)//affichage de tous les registres
            {
                displayRegisters();
            }
            else
            {
                displayRegister(stoi(args[1]));
            }
        }
        else if (args[0] == "address")
        {
            if (nbArgs == 1)
            {
                displayAddress(stoi(args[1]));
            }
            else
            {
                displayAdress(stoi(args[1]), stoi(args[2]));
            }
        }
        else
        {
            errMess.unknownSubCommand();
            return false;
        }

        return true;
    }
    catch (const out_of_range& e)
    {
        errMess.badNumberArgs();
        return false;
    }
    catch (const exception& e)
    {
        errMess.badArgs();
        return false;
    }
}

bool Debugger::dum(const vector<string>& args)
{
    if (args.size() != 3)
    {
        errMess.badNumberArgs();
        return false;
    }
    else
    {
        try
        {
            dumpMem(stoi(args[0]), stoi(args[1]), args[2]);
        }
        catch (const exception& e)
        {
            errMess.badArgs();
            return false;
        }
        return true;
    }
}

bool Debugger::find(const vector<string>& args)
{
    if(args.size() != 1)
    {
        errMess.badNumberArgs();
    }
    try
    {
        int32_t* seq = Search::parseSeq(args);
    }
    catch(const exception& e)
    {
        errMess.badArgs();
    }
    //Lancer la première recherche
    return true;
}

bool Debugger::find_next(const vector<string>& args)
{
    if(!args.empty())
    {
        errMess.badNumberArgs();
        return false;
    }
    //Vérifier si une recherche a été lancée.
    //Continuer la recherche
    return true;
}

}
