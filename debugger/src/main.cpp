/**
 * Un main pour tester le debugger.
 */

#include <iostream>
#include <string>

#include "terminal.hpp"
#include "debugger.hpp"
#include "cpu.hpp"

 /**
  * \mainpage Architecture du debugger :
  * méthode interact de debugger à appeler dans la boucle d'exécution du simulateur.
  *
  * Le debugger a accès à l'état interne du simulateur.
  * Il faut "attacher" le simulateur au debugger au préalable.
  *
  */

 using namespace std;
 using namespace debugger;

 int main(int argc, char* argv[])
 {
    cout.sync_with_stdio(true);
    
    if(argc > 3)
    {
        cerr << "Usage : debugger program [fichier.log]" <<endl;
        exit(1);
    }
    string file_asm(argv[1]);
    if(argc ==3)
    {
       string file_log(argv[2]); 
    }
    else
    {
        string file_log;
    }
    
    cout << "Debugger : " << file_asm << endl;
    CPU simulator;
    simulator.read_program(argv[1]);
    
    Terminal terminal;
    Debugger debugger(terminal, &simulator);
    debugger.debug();

    return 0;
 }
