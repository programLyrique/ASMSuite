#ifndef _MEMORY
#define _MEMORY
#include <cstdint>


//Pas de defin de constantes en C++ !
//#define LOAD 0
//#define STORE 1

namespace mem_inst
{

enum MEM_INST
{
    LOAD,
    STORE
};
}
#define N 65536

class Memory
{
private:
    int32_t* addr;
    int32_t* in;
    int32_t* out;

    /*
     * La mémoire est divisée en 65536 parties de 65536 mots (soit 2³² en tout).
     * -> mécanisme de pagination. Seules les pages qui ont des adresses écrites sont
     * allouées. Une lecture dans une autre page renvoie 0.
     */
    int32_t* memory[N];
public:
    Memory(int32_t* _addr, int32_t* _in, int32_t* _out);
    void load();
    void store();

    /**
     * Interface de lecture avec le debugger
     * @param ad
     * @return 
     */
    int32_t readMem(int ad) const
    {
        if (memory[static_cast<int32_t> (ad) / N] != nullptr)
        {
            return memory[static_cast<int32_t> (ad) / N][static_cast<int32_t> (ad) % N];
        }
        else
        {
            return 0;
        }

    }

    int nbWords() const
    {
        return N;
    }

    long sizeMem() const
    {
        return (long) N * (long) N;
    }

    /**
     * Interface d'écriture pour le debugger
     * @param ad
     * @param val
     */
    void writeMem(int ad, int32_t val)
    {
        if (memory[static_cast<int32_t> (ad) / N] == nullptr)
        {
            memory[static_cast<int32_t> (ad) / N] = new int32_t[N];
        }
        memory[static_cast<int32_t> (ad) / N][static_cast<int32_t> (ad) % N] = val;
    }
};
#endif
