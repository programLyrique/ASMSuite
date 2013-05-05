#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <vector>
#include <string>
#include <sstream>

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
        Terminal(){}
        void prompt();
        static vector<string> parseCommandLine(string line);
        
        virtual ~Terminal(){};

};

}

#endif

