#include "debugger.hpp"
#include <iostream>

using namespace std;

namespace debugger
{

Debugger::Debugger(CommandInterface& inter, CPU* cpu) : interf(inter), errMess(inter), sim(cpu)
{
    /*
     * Initialisation des correspondances de sous-commandes pour les points d'arrêt
     */
    break_commands["line"] = breakpoint::LINE;
    break_commands["label"] = breakpoint::LABEL;
    break_commands["port"] = breakpoint::PORT;
    break_commands["instr"] = breakpoint::INSTR;
    break_commands["adr"] = breakpoint::ADR;

    //On s'arrête au début.
    breakpoints.push_back(new LineBreakpoint(sim, 1));

}


bool Debugger::interact()
{
    bool contDebug = true;
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
        /*ostringstream outPC;
        outPC << "PC : " << sim->getBus_pc();
        interf.answer(outPC);*/
        bool cont = true;
         
         while(cont)
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
                cont = false;
            }
            //addBreakpoint se charge d'indiquer les erreurs

            break;
        case command::DISPLAY:
            cont = !display(args);
            break;
        case command::PRINT:
            for (int i = 0; i < args.size(); i++)
            {
                out << args[i] << " ";
            }
            interf.answer(out);
            cont = false;
            break;
        case command::DUMP:
            cont = !dum(args);
            break;
        case command::SEARCH:
            break;
        case command::SEARCH_NEXT:
            break;
        case command::WRITE:
            cont = !write(args);
            break;
        case command::EXIT:
            cont = false;
            contDebug = false;
            interf.answer("\nExiting..");
            break;
        default:
            errMess.unknownCommand();
            break;
        }
         }
    }
    
    return contDebug;
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
            breakpoint = new LineBreakpoint(sim, stoi(args[1]));
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

bool Debugger::displayRegister(int i)
{
    ostringstream out;
    if(i > sim->getRegisters()->nbRegisters() || i == 0)
    {
        return false;
    }
    out << "REG[" << i << "] = " << sim->getRegisters()->readReg(i-1); //rajouter la bonne valeur
    interf.answer(out);
    return true; //false si le registre est invalide
}

void Debugger::displayRegisters()
{
    ostringstream out;
    int nbRegistres = sim->getRegisters()->nbRegisters();
    for (int i = 1; i <= nbRegistres; i += 2)
    {
        out << "REG[" << i << "] = " << sim->getRegisters()->readReg(i-1)
                << "\t REG[" << (i + 1) << "] = " << sim->getRegisters()->readReg(i) << endl;
    }
    interf.answer(out);
}

bool Debugger::displayAddress(int addr)
{
    cerr << sim->getData_memory()->sizeMem() << endl;
    if(addr < 0 || addr > sim->getData_memory()->sizeMem())
    {
        return false;
    }
    ostringstream out;
    out << "MEM[" << addr << "] = " << sim->getData_memory()->readMem(addr);
    interf.answer(out);
    return true; //false si l'adresse est invalide
}

bool Debugger::displayAdress(int addr, int offset)
{
    if(offset < 0 || addr < 0)
    {
        return false;
    }
    ostringstream out;
    //Affichage 12 lignes par 12 lignes
    int nbLignes = offset / 12;
    for(int i =0; i < nbLignes;i++)
    {
           out.clear(); 
           for(int ad=12*i; ad < offset && ad < sim->getData_memory()->sizeMem(); ad++)
           {
               out << sim->getData_memory()->readMem(ad) << " ";
           }
           interf.answer(out);
    }
    return true; //false si l'adresse ou l'offset sont invalides
}

bool Debugger::dumpMem(int addr, int offset, const string& fileName)
{
    //ostream file(fileName);

    interf.answer("Sauvegarde de la plage mémoire dans le fichier.");
    return true; //false si l'adresse ou l'offset sont invalides
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
    return true;
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
    if (args.size() != 1)
    {
        errMess.badNumberArgs();
    }
    try
    {
        int32_t* seq = Search::parseSeq(args);
    }
    catch (const exception& e)
    {
        errMess.badArgs();
    }
    //Lancer la première recherche
    return true;
}

bool Debugger::find_next(const vector<string>& args)
{
    if (!args.empty())
    {
        errMess.badNumberArgs();
        return false;
    }
    //Vérifier si une recherche a été lancée.
    //Continuer la recherche
    return true;
}

bool Debugger::writeMem(int adresse, int val, int offset)
{
    if(adresse <0 || offset < 0)
    {
        return false;
    }
    for(int ad= adresse; ad < adresse + offset && ad < sim->getData_memory()->sizeMem();ad++)
    {
        sim->getData_memory()->writeMem(ad, static_cast<int32_t>(val));
    }
    return true;
}

bool Debugger::writeReg(int reg, int val)
{
    int nbReg = sim->getRegisters()->nbRegisters();
    if(reg == 0 || reg > nbReg)
    {
        return false;
    }
    sim->getRegisters()->writeReg(reg, static_cast<int32_t>(val));
    return true;
}

bool Debugger::write(const vector<string>& args)
{
    int nbArgs = args.size();
    if (nbArgs == 0)
    {
        return errMess.noSubCommand();
    }

    nbArgs--;
    
    try
    {

        if (args[0] == "adress")
        {
            if(nbArgs == 2)
            {
                writeMem(stoi(args[1]), stoi(args[2]));
            }
            else if(nbArgs == 3)
            {
                writeMem(stoi(args[1]), stoi(args[2]), stoi(args[3]));
            }
            else
            {
                return errMess.badNumberArgs();
            }
                
        }
        else if (args[0] == "register")
        {
            if(nbArgs == 2)
            {
                writeReg(stoi(args[1]), stoi(args[2]));
            }
            else
            {
                return errMess.badNumberArgs();
            }
        }
        else
        {
            return errMess.unknownSubCommand();
        }
    }
    catch (const out_of_range& e)
    {
        return errMess.badNumberArgs();
    }
    catch (const exception& e)
    {
        return errMess.badArgs();
    }
    
    return true;
}

}
