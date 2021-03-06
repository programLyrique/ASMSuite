#include "debugger.hpp"

#include <iostream>
#include <iomanip>
#include <fstream>
#include <chrono>

#include "commandInterface.hpp"
#include "terminal.hpp"

using namespace std;

namespace debugger
{

Debugger::Debugger(CommandInterface& inter, CPU* cpu) :
interf(inter), errMess(inter),
sim(cpu), n_instr(1), nb_cycles(0), pc_lim(-1)
{

    //On attache le debugger à l'interface

    //CommandInterface:attach_debugger(this);

    /*
     * Initialisation des correspondances de sous-commandes pour les points d'arrêt
     */
    break_commands["line"] = breakpoint::LINE;
    break_commands["label"] = breakpoint::LABEL;
    break_commands["port"] = breakpoint::PORT;
    break_commands["instr"] = breakpoint::INSTR;
    break_commands["adr"] = breakpoint::ADR;

    //Mise en place d'une recherche sur la mémoire
    if (cpu != nullptr)
    {
        search = new Search(*(sim->getData_memory()));
    }
}

bool Debugger::interact()
{
    chronometre.press();//on stoppe le chrono car le temps de debugage ne fait pas partie des festivités
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

    if (sim->getBus_pc() == pc_lim)
    {
        breaks = true;
        pc_lim = -1;
    }
    if (n_instr > 0)
    {
        n_instr--;
    }

    //Si point d'arrêt, ou n exécutions, ou interruption par ctrl+c
    // Un appui à crtl+c ici terminera le programme
    if (breaks || n_instr == 0 || Terminal::isInterrupted())
    {
        /*ostringstream outPC;
        outPC << "PC : " << sim->getBus_pc();
        interf.answer(outPC);*/
        bool cont = true;

        while (cont)
        {
            vector<string> args;
            //On affiche l'invite pour rentrer une commande de debogage
            command::Command command = interf.prompt(nb_cycles, sim->getBus_pc(), args);


            //Déclaration pour les variables du switch (plutôt que d'utiliser -fpermissive)
            Breakpoint * breakpoint; //pourtant locale...
            ostringstream out;
            switch (command)
            {
            case command::BREAKPOINT:
                if ((breakpoint = addBreakpoint(args)) != nullptr)
                {
                    addBreakpoint(breakpoint);
                }
                //addBreakpoint se charge d'indiquer les erreurs
                n_instr = 0; //On remet le compteur de suivi d'exécution à 0
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
                dump(args);
                break;
            case command::SEARCH:
                find(args);
                break;
            case command::SEARCH_NEXT:
                find_next(args);
                break;
            case command::WRITE:
                write(args);
                break;
            case command::RUN:
                cont = false;
                n_instr = -1;
                break;
            case command::EXIT:
                cont = false;
                contDebug = false;
                interf.answer("\nExiting..");
                break;
            case command::NEXT:
                cont = false;
                n_instr = 1;
                break;
            case command::STEP:
                step(args);
                cont = false;
                break;
                /*Equivalent à mettre un breakpoint sur PC+1 où PC est enregistré au moment
                 * de la commande.
                 * Mais problème de cette solution : il faudrait supprimer le breakpoint une fois atteint.
                 * On préfère faire une gestion séparée.
                 */
            case command::UNTIL:
                pc_lim = sim->getBus_pc() + 1;
                cont = false;
                n_instr = -1;
                break;
            case command::HELP:
                errMess.notSupported();
                break;
            case command::INFO:
                info(args);
                break;
            case command::SHELL:
                shell(args);
                break;
            case command::TIME:
                time(args);
                break;
            case command::CLEAR:
                clear(args);
                break;
            default:
                errMess.unknownCommand();
                break;
            }
        }
    }

    //Si l'arrêt était dû à crtrl+c, on remet ctrl+c comme interruption du programme
    // débugué, et pas du debugger
    if (Terminal::isInterrupted())
    {
        Terminal::resetInterrupt();
    }

    chronometre.press();//On relance le chronometre
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
            breakpoint = new InstrBreakpoint(*(sim->getControl_unit()), dis.getInst_type(args[1]), dis.getOpcode(args[1]));
            break;
        case breakpoint::ADR:
            if (nbArgs == 1)
            {
                int adr = stoi(args[1]);
                breakpoint = new AdrBreakpoint(*sim, adr, adr + 1);

            }
            else if (nbArgs == 2)
            {
                breakpoint = new AdrBreakpoint(*sim, stoi(args[1]), stoi(args[2]));
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
    if (i > sim->getRegisters()->nbRegisters() || i == 0)
    {
        return false;
    }
    out << "REG[" << i << "] = " << sim->getRegisters()->readReg(i - 1); //rajouter la bonne valeur
    interf.answer(out);
    return true; //false si le registre est invalide
}

void Debugger::displayRegisters()
{
    ostringstream out;
    int nbRegistres = sim->getRegisters()->nbRegisters();
    for (int i = 1; i <= nbRegistres; i += 2)
    {
        out << "REG[" << i << "] = " << sim->getRegisters()->readReg(i - 1)
                << "\t REG[" << (i + 1) << "] = " << sim->getRegisters()->readReg(i) << endl;
    }
    interf.answer(out);
}

bool Debugger::displayAddress(int addr)
{
    if (addr < 0 || addr > sim->getData_memory()->sizeMem())
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
    if (offset < 0 || addr < 0)
    {
        return false;
    }
    //Affichage 12 lignes par 12 lignes
    int nbLignes = offset / 12 + 1;
    for (int i = 0; i < nbLignes; i++)
    {
        ostringstream out;
        for (int ad = addr + 12 * i; ad < addr + 12 * (i + 1) && ad < addr + offset && ad < sim->getData_memory()->sizeMem(); ad++)
        {
            out << setw(10) << sim->getData_memory()->readMem(ad) << " ";
        }
        interf.answer(out);
    }
    return true; //false si l'adresse ou l'offset sont invalides
}

bool Debugger::dumpMem(int addr, int offset, const string& fileName)
{
    ostringstream out;
    out << "Sauvegarde de la plage mémoire dans le fichier " << fileName;

    const int size_buf = 128;
    char buffer[sizeof (int32_t) * size_buf];

    ofstream file(fileName, ofstream::binary | ofstream::trunc);

    for (int ad = addr; ad < addr + offset; ad += size_buf)
    {
        int j = 0;
        for (; j < size_buf && ad + j < addr + offset; j++)
        {
            int32_t word = sim->getData_memory()->readMem(ad + j);
            //séparation de l'int en octets
            for (int k = 0; k < sizeof (int32_t); k++)
            {
                buffer[sizeof (int32_t) * j + k] = (word >> (sizeof (int32_t) - k) * 8) & 0xFF; //big endian supposé
            }
        }
        //Ecriture du buffer
        file.write(buffer, j * sizeof (int32_t));
    }
    file.close();
    interf.answer(out);
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

bool Debugger::dump(const vector<string>& args)
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
    vector<int32_t>* seq;
    if (args.size() < 1)
    {
        errMess.badNumberArgs();
    }
    try
    {
        seq = Search::parseSeq(args);
    }
    catch (const exception& e)
    {
        errMess.badArgs();
    }
    //Lancer la première recherche
    search->new_search(seq);
    int addr = search->find_next();

    if (addr != -1)
    {
        ostringstream out;
        out << "Concordance à MEM[" << addr << "]";
        interf.answer(out);
    }
    else
    {
        interf.answer("Plus de résultats");
    }

    return addr != -1;
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
    if (!search->isSearching())
    {
        interf.errorMessage("Pas de recherche en cours");
        return false;
    }
    int addr = search->find_next();

    if (addr != -1)
    {
        ostringstream out;
        out << "Concordance à MEM[" << addr << "]";
        interf.answer(out);
    }
    else
    {
        interf.answer("Plus de résultats");
    }

    return addr != -1;
}

bool Debugger::writeMem(int adresse, int val, int offset)
{
    if (adresse < 0 || offset < 0)
    {
        return false;
    }
    for (int ad = adresse; ad < adresse + offset && ad < sim->getData_memory()->sizeMem(); ad++)
    {
        sim->getData_memory()->writeMem(ad, static_cast<int32_t> (val));
    }
    return true;
}

bool Debugger::writeReg(int reg, int val)
{
    int nbReg = sim->getRegisters()->nbRegisters();
    if (reg == 0 || reg > nbReg)
    {
        return false;
    }
    sim->getRegisters()->writeReg(reg - 1, static_cast<int32_t> (val));
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

        if (args[0] == "address")
        {
            if (nbArgs == 2)
            {
                writeMem(stoi(args[1]), stoi(args[2]));
            }
            else if (nbArgs == 3)
            {
                writeMem(stoi(args[1]), stoi(args[3]), stoi(args[2]));
            }
            else
            {
                return errMess.badNumberArgs();
            }

        }
        else if (args[0] == "register")
        {
            if (nbArgs == 2)
            {
                writeReg(stoi(args[1]), stoi(args[2]));
            }
            else
            {
                return errMess.badNumberArgs();
            }
        }
        else if (args[0] == "port")
        {
            if (nbArgs != 3)
            {
                return errMess.badNumberArgs();
            }
            if (args[1] == "in")
            {
                errMess.notSupported();
            }
            else if (args[1] == "out")
            {
                writePort(stoi(args[2]), stoi(args[3]));
            }
            else
            {
                return errMess.badArgs();
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

bool Debugger::step(const vector<string>& args)
{
    try
    {
        n_instr = stoi(args[0]);
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

bool Debugger::writePort(int port, int val)
{
    //Sauvegarde des valeurs sur les bus
    int in = sim->getBus_in();
    int out2 = sim->getBus_out2();
    //Nouvelles valeurs sur les bus
    sim->setBus_in(port);
    sim->setBus_out2(val);
    //Ecriture
    sim->getIO()->output();
    //Restauration des bus
    sim->setBus_in(in);
    sim->setBus_out2(out2);
    return true;
}

void Debugger::addBreakpoint(Breakpoint* breakpoint)
{
    breakpoints.push_back(breakpoint);
}

void Debugger::clearBreakpoint(int num)
{
    breakpoints.erase(breakpoints.begin() + num);
}

bool Debugger::info(const vector<string>& args)
{
    if (args.size() != 1)
    {
        return errMess.badNumberArgs();
    }

    if (args[0] == "breakpoint")
    {
        for (int i = 0; i < breakpoints.size(); ++i)
        {
            ostringstream out;
            out << i << " : " << breakpoints[i]->describe();
            ;
            interf.answer(out);
        }
    }
    else
    {
        return errMess.badArgs();
    }

    return true;
}

bool Debugger::clear(const vector<string>& args)
{
    if (args.size() != 1)
    {
        return errMess.badNumberArgs();
    }
    try
    {
        clearBreakpoint(stoi(args[0]));
    }
    catch (const exception& ex)
    {
        errMess.badArgs();
    }

    return true;
}

bool Debugger::shell(const vector<string>& args)
{
    //Reconcaténer les tokens
    string concat;
    for (int i = 0; i < args.size(); ++i)
    {
        concat += " " + args[i];
    }
    return system(concat.c_str());
}

bool Debugger::time(const vector<string>& args)
{
    if(args.size() !=1)
    {
        return errMess.badNumberArgs();
    }
    
    if(args[0] == "start")
    {
        chronometre.start();
    }
    else if(args[0] == "stop")
    {
        ostringstream out;
        out << "Temps écoulé : " << chronometre.timeElapsed().count() << " millisecondes";
        interf.answer(out);
    }
    else
    {
        return errMess.badArgs();
    }
}

}
