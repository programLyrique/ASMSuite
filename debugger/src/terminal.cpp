#include "terminal.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

namespace debugger
{

    void Terminal::prompt()
    {
        cout << "> " << flush;
        string in;
        getline(cin, in); // on lit l'entrée
    }

    /**
     * \brief Parser la ligne de commande en séparant selon les espaces
     */
    vector<string> Terminal::parseCommandLine(string line)
    {
        vector<string> tokens;
        istringstream iss(line);
        copy(istream_iterator<string>(iss),
        istream_iterator<string>(),
         back_inserter<vector<string> >(tokens));

         return tokens;
    }
    
    void Terminal::analyseTokens(vector<string> tokens)
    {
        
    }

}
