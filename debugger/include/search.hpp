/* 
 * File:   Search.hpp
 * Author: pierre
 *
 * Created on 6 mai 2013, 18:05
 */

#ifndef SEARCH_HPP
#define	SEARCH_HPP

#include <cstdint>
#include <vector>
#include <string>
#include <algorithm>

#include "memory.hpp"


namespace debugger
{
/**
 * Pour effectuer des recherches dans la mémoire.
 * Entrée sous la forme d'une suite de nombres hexadécimaux de 32 bits séparés par
 *  des espaces
 * \example FFFF 56
 * @param mem
 */
class Search
{
public:
    Search(Memory& mem);
    Search(const Search& orig);
    
    /**
     * Lancer une nouvelle recherche
     * @param seq
     * @param size_seq
     */
    void new_search(int32_t* seq, int size_seq);
    
    /**
     * Lancer une nouvelle recherche limitée à l'intervalle 
     * d'adresse [debut, debut + offset [
     * @param seq
     * @param size_seq
     * @param debut
     * @param fin
     */
    void new_search(int32_t* seq, int size_seq, int debut, int offset);
    /**
     * Renvoie la prochaine adresse qui correspond à la séquence
     * @return -1 s'il n'y a plus rien
     */
    int find_next();
    
    static int32_t* parseSeq(const std::vector<std::string>& args);
    
    bool isSearching()
    {
        return search;
    }
    virtual ~Search();
private:
    const Memory& mem;
    std::int32_t* seq;
    int size_seq;
    int current;
    int debut;
    int fin;
    bool search;
};

}
#endif	/* SEARCH_HPP */

