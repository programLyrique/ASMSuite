#include "terminal.hpp"

#include <algorithm>
#include <iterator>

using namespace std;

namespace debugger
{
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
    }
    
    command::Command Terminal::prompt(vector<string>& args)
    {
        cout << "\n> " << flush;
        string in;
        getline(cin, in); // on lit l'entrée
        
        
        vector<string> tokens = parseCommandLine(in);
        if(tokens.size() == 0)
        {
            return command::ERROR;
        }
        else
        {
            args = tokens;
            //Supprimer le premier élément (qui  est le nom de la commande)
            args.erase(args.begin());//Déjà supprimé par prompt
            return analyseTokens(tokens);
        }
        
    }

    vector<string> Terminal::parseCommandLine(string line)
    {
        vector<string> tokens;
        istringstream iss(line);
        copy(istream_iterator<string>(iss),
        istream_iterator<string>(),
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
        catch(const out_of_range& e)
        {
            com = command::ERROR;
        }
        return  com;
    }

}
