#include "terminal.hpp"

#include <iostream>
#include <algorithm>
#include <iterator>

using namespace std;

namespace debugger
{

    command::Command Terminal::prompt(vector<string>& args)
    {
        cout << "> " << flush;
        string in;
        getline(cin, in); // on lit l'entrée
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
        
    }

}
