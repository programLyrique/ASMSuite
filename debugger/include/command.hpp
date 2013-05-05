/* 
 * File:   Command.hpp
 * Author: pierre
 *
 * Created on 6 mai 2013, 00:41
 */

#ifndef COMMAND_HPP
#define	COMMAND_HPP

class Command
{
public:
    virtual void operator() = 0;
    virtual ~Command();
private:

};

#endif	/* COMMAND_HPP */

