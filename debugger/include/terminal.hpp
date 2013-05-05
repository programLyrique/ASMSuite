#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <vector>
#include <string>
#include <sstream>
#include <map>

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

        Terminal()
        {
        }
        /**
         * Ask for a new command by the debugger.
         */
        void prompt();
        /**
         * Analyse les composantes de la commande 
         * et fait l'action correspondante.
         * @param tokens
         */
        void analyseTokens(vector<string> tokens);
        /**
         * \brief Parser la ligne de commande en séparant selon les espaces
         */
        static vector<string> parseCommandLine(string line);

        virtual ~Terminal()
        {
        };
    private:
        /// Stocker les commandes vers un foncteur
        map<string, Command&> commands;

    };

}

#endif

