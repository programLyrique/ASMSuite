#ifdef COMMAND_INTERFACE_H
#define COMMAND_INTERFACE_H

namespace debugger
{

/**
 * L'interface par laquelle l'utilisateur interagit avec le debogueur.
 */
class CommandInterface
{
    public:
     virtual void prompt() = 0;
};

}

#define COMMAND_INTERFACE_H
