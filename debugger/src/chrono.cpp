/* 
 * File:   Chrono.cpp
 * Author: pierre
 * 
 * Created on 16 mai 2013, 21:45
 */

#include "chrono.hpp"

using namespace std::chrono;

namespace debugger
{

Chrono::Chrono() : 
startTime(high_resolution_clock::now()), 
        paused(false), 
        elapsedTime(high_resolution_clock::duration::zero())
{
}



void Chrono::press()
{
    auto time_now = high_resolution_clock::now();
    if (!paused)
    {
        elapsedTime += duration_cast<milliseconds>(time_now - startTime);
        paused = true;
    }
    else
    {
        startTime = time_now;
    }
    paused = !paused;

}

void Chrono::start()
{
    startTime = high_resolution_clock::now();
    paused = false;
    elapsedTime = duration_cast<milliseconds>(high_resolution_clock::duration::zero());
}

high_resolution_clock::duration Chrono::timeElapsed() const
{
    return elapsedTime;
}

Chrono::~Chrono()
{
}

void Chrono::reset()
{
    start();
}

}

