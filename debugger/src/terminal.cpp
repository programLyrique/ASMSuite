#include "terminal.hpp"

#include <algorithm>
#include <iterator>

using namespace std;

namespace debugger
{

bool CommandInterface::interrupt = false;

Terminal::Terminal()
{
    /**
     * Initialisation des commandes
     */

    //Breakpoints
    commands["breakpoint"] = command::BREAKPOINT;
    commands["display"] = command::DISPLAY;
    commands["dump"] = command::DUMP;
    commands["print"] = command::PRINT;
    commands["write"] = command::WRITE;
    commands["find"] = command::SEARCH;
    commands["find-next"] = command::SEARCH_NEXT;
    commands["run"] = command::RUN;
    commands["continue"] = command::RUN;
    commands["c"] = command::RUN;
    commands["r"] = command::RUN;
    commands["next"] = command::NEXT;
    commands["n"] = command::NEXT;
    commands["step"] = command::STEP;
    commands["until"] = command::UNTIL;
    commands["help"] = command::HELP;
    commands["h"] = command::HELP;
    commands["info"] = command::INFO;
    commands["!"] = command::SHELL;
    commands["time"] = command::TIME;
    commands["clear"] = command::CLEAR;
    commands["exit"] = command::EXIT;

    //Mise en place du gestionnaire d'interruption
    struct sigaction action, oldAction;

    action.sa_handler = interrupt_handler; //
    sigemptyset(&action.sa_mask);
    action.sa_flags = SA_RESTART;
    sigaction(SIGINT, &action, &oldAction);
}

command::Command Terminal::prompt(int nb_cycles, int pc, vector<string>& args)
{
    cout << "\n" << nb_cycles << " [PC=" << pc << "] > " << flush;
    string in;
    getline(cin, in); // on lit l'entrée

    if (cin.eof())//appui sur ctrl+d
    {
        return command::EXIT;
    }

    vector<string> tokens = parseCommandLine(in);
    if (tokens.size() == 0)
    {
        return command::ERROR;
    }
    else
    {
        args = tokens;
        //Supprimer le premier élément (qui  est le nom de la commande)
        args.erase(args.begin()); //Déjà supprimé par prompt
        return analyseTokens(tokens);
    }

}

vector<string> Terminal::parseCommandLine(string line)
{
    vector<string> tokens;
    istringstream iss(line);
    copy(istream_iterator<string > (iss),
         istream_iterator<string > (),
         back_inserter<vector<string> >(tokens));

    return tokens;
}

command::Command Terminal::analyseTokens(vector<string> tokens)
{
    command::Command com;
    try
    {
        com = commands.at(tokens[0]);
    }
    catch (const out_of_range& e)
    {
        com = command::ERROR;
    }
    return com;
}

void Terminal::interrupt_handler(int signal)
{
    if (signal == SIGINT && !CommandInterface::interrupt)//appui sur ctrl+c
    {
        cerr << "\nInterruption du programme." << endl;
        CommandInterface::interrupt = true;

    }
    else
    {
        exit(0);
    }
}

}
