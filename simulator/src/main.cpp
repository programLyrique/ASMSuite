#include "control_unit.hpp"
#include "alu.hpp"
#include "memory.hpp"
#include "registers.hpp"
#include "cpu.hpp"

#include <iostream>

using namespace std;

/*Le debugger compile aussi les fichiers du simulateur.
 * Ceci permet d'éviter un conflit de main entre debugger et simulateur
 */
#ifdef SIMULATOR

int main(int argc, char* argv[])
{
    cout.sync_with_stdio(true);

    if (argc > 2 || argc == 1)
    {
        cerr << "Usage : simulator program " << endl;
        exit(1);
    }

    cout << "Simulator : " << argv[1] << endl;
    CPU simulator;
    simulator.read_program(argv[1]);
    simulator.run();
    cout << "Fin de l'exécution" <<  endl;

    return 0;
}


#endif