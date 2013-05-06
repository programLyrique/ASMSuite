#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <unordered_map>

#include "debugger.hpp"
#include "command.hpp"
#include "commandInterface.hpp"


using namespace std;

namespace debugger
{

    /**
     * Une interface console pour interagir avec le debugger.
     */
    class Terminal : public CommandInterface
    {
    public:

        Terminal();
        /**
         * Demande une nouvelle commande au debugger.
         * \arg args sera rempli avec les arguments de la commande
         * \return le type de la commande
         */
        enum command::Command prompt(vector<string>& args);
        /**
         * Analyse les composantes de la commande 
         * et fait l'action correspondante.
         * @param tokens
         */
       enum command::Command analyseTokens(vector<string> tokens);
        /**
         * \brief Parser la ligne de commande en séparant selon les espaces
         */
        static vector<string> parseCommandLine(string line);
        
        void errorMessage(string error)
        {
            cerr << error << endl;
        }
        
        void answer(const ostringstream& message)
        {
            cout << message.str() << endl;
        }
        
        void answer(const string& message)
        {
            cout << message << endl;
        }

        virtual ~Terminal()
        {
        }
    private:
        /// Stocker les commandes vers un enum de commandes
        unordered_map<string, command::Command> commands;

    };

}

#endif