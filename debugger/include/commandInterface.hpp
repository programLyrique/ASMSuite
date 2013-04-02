#ifdef COMMAND_INTERFACE_H
#define COMMAND_INTERFACE_H

namespace debugger
{

/**
 * L'interface par laquelle l'utilisateur interragit avec le debogueur.
 */
class CommandInterface
{
    virtual void prompt() = 0;
};

}

#define COMMAND_INTERFACE_H
