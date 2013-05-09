#ifndef COMMAND_INTERFACE_H
#define COMMAND_INTERFACE_H

#include <vector>
#include <sstream>
#include <string>

#include "command.hpp"

using namespace std;


namespace debugger
{

/**
 * L'interface par laquelle l'utilisateur interagit avec le debogueur.
 */
class CommandInterface
{
public:
    /**
     * Appeler en cas d'arrêt : choisit la nouvelle action à faire
     * @param args
     * @return 
     */
    virtual enum command::Command prompt(int nb_cycles, int pc, vector<string>& args) = 0;

    /**
     * Affiche un message en cas d'erreur.
     * @param error
     */
    virtual void errorMessage(string error) = 0;

    /**
     * Pour afficher les réponses du debugger
     * @param message
     */
    virtual void answer(const string& message) = 0;

    virtual void answer(const ostringstream& message) = 0;

    virtual ~CommandInterface()
    {
    }

    static bool isInterrupted() { return interrupt;}
    
    static void resetInterrupt(){interrupt = false;}

protected:
    static bool interrupt;

};

}

#endif

