/* 
 * File:   Search.hpp
 * Author: pierre
 *
 * Created on 6 mai 2013, 18:05
 */

#ifndef SEARCH_HPP
#define	SEARCH_HPP

#include <cstdint>

class Memory;

namespace debugger
{
/**
 * Pour effectuer des recherches dans la mémoire.
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

