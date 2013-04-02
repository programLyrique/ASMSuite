#include "terminal.hpp"
#include <iostream>

using namespace std;

namespace debugger 
{

void Terminal::prompt()
{
    cout << "> " << flush;
}

}
