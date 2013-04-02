#ifndef TERMINAL_HPP
#define TERMINAL_HPP

namespace debugger
{

/**
 * Une interface console pour interagir avec le debugger.
 */ 
class Terminal : public commandInterface
{
    public:
        void prompt();
};

}

#endif

