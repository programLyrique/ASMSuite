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
class Memory {
    private:
  int32_t* addr;
  int32_t* in;
  int32_t* out;

  int32_t* memory[N]; // la mémoire est divisée en 65536 parties de 65536 mots (soit 2³² en tout).
    public:
        Memory(int32_t* _addr, int32_t* _in, int32_t* _out);
        void load ();
        void store ();
        int32_t readMem(int ad) const 
        { 
            if(memory[static_cast<int32_t>(ad) / N] != NULL)
            {
                return memory[static_cast<int32_t>(ad) / N][static_cast<int32_t>(ad) % N];
            }
            else
            {
                return 0;
            }

        }
        int nbWords() const { return N;}
        long sizeMem() const { return (long)N*(long)N;}
        void writeMem(int ad, int32_t val) 
        { 
            memory[static_cast<int32_t>(ad) / N][static_cast<int32_t>(ad) % N] = val;
        }
};
#endif
