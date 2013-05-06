/* 
 * File:   Search.cpp
 * Author: pierre
 * 
 * Created on 6 mai 2013, 18:05
 */

#include "search.hpp"


using namespace std;

namespace debugger
{

    Search::Search(Memory& mem) : mem(mem), current(0)
    {
    }

    void Search::new_search(int32_t* seq, int size_seq)
    {
        current = 0;
        //mettre fin à la taille de la mémoire
        this->seq = seq;
        this->size_seq = size_seq;
    }
    
    void Search::new_search(int32_t* seq, int size_seq, int debut, int offset)
    {
        current = debut;
        fin =debut + offset;
        this->seq=seq;
        this->size_seq = size_seq;
    }
    
    int Search::find_next()
    {
        return current;
    }

    Search::~Search()
    {
    }

}
