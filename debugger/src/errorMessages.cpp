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

bool ErrorMessages::badNumberArgs()
{
    inter.errorMessage("Mauvais nombre d'arguments");
    return false;
}

bool ErrorMessages::badArgs()
{
    inter.errorMessage("Mauvais arguments");
    return false;
}

bool ErrorMessages::unknownSubCommand()
{
    inter.errorMessage("Sous-commande inconnue");
    return false;
}

bool ErrorMessages::unknownCommand()
{
    inter.errorMessage("Commande inconnue");
    return false;
}

bool ErrorMessages::noSubCommand()
{
    inter.errorMessage("Absence de sous-commande");
    return false;
}

ErrorMessages::~ErrorMessages()
{
}

}
