/* 
 * File:   Search.cpp
 * Author: pierre
 * 
 * Created on 6 mai 2013, 18:05
 */

#include "search.hpp"
#include <sstream>

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
        delete[] this->seq;
        this->seq = seq;
        this->size_seq = size_seq;
        search = true;
    }
    
    void Search::new_search(int32_t* seq, int size_seq, int debut, int offset)
    {
        current = debut;
        fin =debut + offset;
        delete[] this->seq;
        this->seq=seq;
        this->size_seq = size_seq;
        search = true;
    }
    
    int Search::find_next()
    {
        //Mettre search à false si la recherche est finie
        return current;
    }

    Search::~Search()
    {
        delete[] seq;
    }
    
    int32_t* Search::parseSeq(const std::vector<std::string>& args)
    {
        int nbNumbers = args.size();
        int32_t * seq = new int32_t[nbNumbers];
        for(int i =0; i < nbNumbers ; i++)
        {
            stringstream conv;
            int32_t nb;
            conv << args[i];
            conv >> nb;
            seq[i] = nb;
        }
        
        return seq;
    }

}
