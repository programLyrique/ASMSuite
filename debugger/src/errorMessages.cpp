/* 
 * File:   ErrorMessages.cpp
 * Author: pierre
 * 
 * Created on 6 mai 2013, 19:22
 */

#include "errorMessages.hpp"


namespace debugger
{

ErrorMessages::ErrorMessages(CommandInterface& interf) : inter(interf)
{
}

void ErrorMessages::badNumberArgs()
{
    inter.errorMessage("Mauvais nombre d'arguments");
}

void ErrorMessages::badArgs()
{
    inter.errorMessage("Mauvais arguments");
}

void ErrorMessages::unknownSubCommand()
{
    inter.errorMessage("Sous-commande inconnue");
}

void ErrorMessages::unknownCommand()
{
    inter.errorMessage("Commande inconnue");
}

void ErrorMessages::noSubCommand()
{
    inter.errorMessage("Absence de sous-commande");
}

ErrorMessages::~ErrorMessages()
{
}

}
