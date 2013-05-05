/**
 * Un main pour tester le debugger.
 */

#include <iostream>
#include <string>

#include "terminal.hpp"

 /**
  * \mainpage Architecture du debugger :
  * méthode interact de debugger à appeler dans la boucle d'exécution du simulateur.
  *
  * Le debugger a accès à l'état interne du simulateur.
  * Il faut "attacher" le debugger au simulateur au préalable.
  *
  */

 using namespace std;
 using namespace debugger;

 int main(int argc, char* argv[])
 {
    cout << "Debugger" << endl;

    string in;
    
    getline(cin, in);

    vector<string> tokens = Terminal::parseCommandLine(in);

    for(int i = 0; i < tokens.size() ; i++)
    {
        cout << tokens[i] << endl;
    }
    return 0;
 }
