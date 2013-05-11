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

    Search::Search(Memory& mem) : mem(mem), current(0), search(false)
    {
    }

    void Search::new_search(vector<int32_t>* seq)
    {
        current = -1;
        //mettre fin à la taille de la mémoire
        delete this->seq;
        this->seq = seq;
        search = true;
    }
    
    void Search::new_search(vector<int32_t>* seq,  int debut, int offset)
    {
        current = debut - 1;
        fin =debut + offset;//Gérer le cas fin > taille mémoire
        delete[] this->seq;
        this->seq=seq;
        search = true;
    }
    
    int Search::find_next()
    {
        //Mettre search à false si la recherche est finie
        //Algo trivial. On pourrait utiliser KMP pour aller plus vite
        
        int j = 0;
        current++;
        for(int i = current  ; i < fin - seq->size(); i++)
        {
            j = 0;
            for(; j < seq->size();j++)
            {
                if(mem.readMem(i+j) != (*seq)[j])
                {
                    break;
                }
            }
            if(j == seq->size())
            {
                return  i;    
            }
        }
        return -1;
    }

    Search::~Search()
    {
        delete seq;
    }
    
    vector<int32_t>* Search::parseSeq(const std::vector<std::string>& args)
    {
        int nbNumbers = args.size();
        vector<int32_t> * seq = new vector<int32_t>(nbNumbers);
        for(int i =0; i < nbNumbers ; i++)
        {
            stringstream conv;
            int32_t nb;
            conv << args[i];
            conv >> nb;
            (*seq)[i] = nb;
        }
        
        return seq;
    }

}
