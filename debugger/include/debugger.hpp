#ifndef DEBUGGER_H
#define DEBUGGER_H


#include <vector>
#include <unordered_map>
#include <stdexcept>   
#include <sstream>
#include <ostream>

#include "command.hpp"
#include "commandInterface.hpp"
#include "breakpoint.hpp"
#include "search.hpp"
#include "errorMessages.hpp"

namespace debugger
{

    class CPU;

    /**
     * La classe en charge de la gestion du debogage.
     *
     * Il faut « attacher » un debugger à un simulateur via la méthode
     * attach du simulateur.
     * \todo laisser charger un fichier qui contienne des commandes pour le debugger
     * à exécuter à chaque breakpoint
     */
    class Debugger
    {
    private:

        CPU* sim;

        CommandInterface& interf;
        
        ErrorMessages errMess;

        vector<Breakpoint*> breakpoints;
        
        //Search search;
        
        unordered_map<string, breakpoint::Breakpoint_t> break_commands;
        
        /* Méthodes pour parser les arguments des commandes*/
        
        /**
         * Etudie les arguments pour créer le bon type de breakpoints
         * @param args
         * @return null if the breakpoint is invalid
         */
        Breakpoint* addBreakpoint(const vector<string>& args);
        
        /**
         * Affiche les informations demandées
         * @param rgs
         * \return false si l'affichage a échoué
         */
        bool display(const vector<string>& args);
        /**
         * Enregistre dans un fichier la plage mémoire demandée
         * @param args
         * @return 
         */
        bool dum(const vector<string>& args);
        /**
         * Lance une recherche et renvoie le premier résultat
         * @param args
         * @return 
         */
        bool find(const vector<string>& args);
        /**
         * Continue la recherche en renvoyant le résultat suivant s'il existe
         * @param args
         * @return 
         */
        bool find_next(const vector<string>& args);
        
        /**
         * Ecrire dans un registre ou dans la mémoire
         * @param args
         * @return 
         */
        bool write(const vector<string>& args);
    public:
        /**
         *
         */
        Debugger(CommandInterface& inter);

        /**
         * Cette méthode est appelée par la fonction attach de Simulator.
         */
            void registerSimulator(CPU* s)
            {
                sim = s;
            }

        /**
         * Dans la boucle principale du simulateur. Stoppe l'exécution, affiche les
         * informations demandées, inspecte le simulateur.
         * @return false si le simulateur doit être arrêté.
         */
        bool interact();
        
        //Méthodes d'affichage
        /**
         * Affiche un registre
         * @param i
         */
        bool displayRegister(int r);
        
        /**
         * Affiche les valeurs de tous les registres;
         */
        void displayRegisters();
        
        /**
         * Affiche la valeur stockée à l'adresse demandée
         * @param addr
         */
        bool displayAddress(int addr);
        
        /**
         * Affiche la plage mémoire [addr, addr+offset [
         * @param addr
         * @param offset
         */
        bool displayAdress(int addr, int offset);
        
        /**
         * Sauvegarde la plage mémoire voulue dans un fichier.
         * @param addr
         * @param offset
         * @param file
         */
        bool dumpMem(int addr, int offset, const string& fileName);
        
        /**
         * Ecris dans la mémoire une valeur ou une plage de valeurs
         * @param adresse
         * @param val
         * @param offset décalage,0 par défaut
         * \return false si échec (mauvais paramètres, par exemple)
         */
        bool writeMem(int adresse, int val, int offset =0);
        /**
         * Ecris une valeur dans un registre
         * @param reg
         * @param val
         * \return false si échec
         */
        bool writeReg(int reg, int val);
        virtual ~Debugger();

    };

}

#endif
