/* 
 * File:   Chrono.hpp
 * Author: pierre
 *
 * Created on 16 mai 2013, 21:45
 */

#ifndef CHRONO_HPP
#define	CHRONO_HPP

#include <chrono>

using namespace std::chrono;
namespace debugger
{

class Chrono
{
public:
    Chrono();
    void press();
    void start();
    void reset();
    high_resolution_clock::duration timeElapsed() const;
    virtual ~Chrono();
private:
    high_resolution_clock::time_point startTime;//on pourrait le faire en nanosecondes...
    high_resolution_clock::duration elapsedTime;
    bool paused;
};

}

#endif	/* CHRONO_HPP */

