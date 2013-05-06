/* 
 * File:   ErrorMessages.hpp
 * Author: pierre
 *
 * Created on 6 mai 2013, 19:22
 */

#ifndef ERRORMESSAGES_HPP
#define	ERRORMESSAGES_HPP

#include "commandInterface.hpp"

namespace debugger
{
    /**
     * Pour simplifier l'affichage de messages d'erreurs récurrents
     * @param interf
     */
    class ErrorMessages
    {
    public:
        ErrorMessages(CommandInterface& interf);
        void badNumberArgs();
        void badArgs();
        void unknownSubCommand();
        void unknownCommand();
        void noSubCommand();
        virtual ~ErrorMessages();
    private:
        CommandInterface& inter;
    };

}

#endif	/* ERRORMESSAGES_HPP */

