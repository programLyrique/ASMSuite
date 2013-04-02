#ifndef _MEMORY
#define _MEMORY
#include <cstdint>
#define LOAD 0
#define STORE 1
#define N 65536
class Memory {
    private:
        int32_t* addr;
        int32_t* in;
        int32_t* out;

        int32_t memory[N];
    public:
        Memory(int32_t* _addr, int32_t* _in, int32_t* _out);
        void load ();
        void store ();
};
#endif

