#ifndef _MEMORY
#define _MEMORY
#define DATA_MEM_SIZE 65536
#define PROG_MEM_SIZE 65536
class Memory {
    private:
        int* addr;
        int* in;
        int* out;

    public:
        virtual void load () = 0;
        virtual void store () = 0;
};

class Data_Memory:Memory {
    private:
        int memory[DATA_MEM_SIZE];
};

class Program_Memory:Memory {
    private:
        int memory[PROG_MEM_SIZE];
};
#endif

