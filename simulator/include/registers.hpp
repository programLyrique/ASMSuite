#ifndef _REGISTERS
#define _REGISTERS
#include <cstdint>
#define NB_REGISTERS 32
class Registers {
    private:
        int32_t* in;
        int32_t* out1;
        int32_t* out2;

        int32_t registers[NB_REGISTERS];
    public:
        Registers (int32_t* _in, int32_t* _out1, int32_t* _out2);
        void read (int reg_out1, int reg_out2);
        void write (int reg_in);
        /**
         * Méthodes pour le debugger
         * @param r
         * @return 
         */
        int32_t readReg(int r) const { return registers[r];}
        int nbRegisters() const { return NB_REGISTERS;}
        void writeReg(int r, int32_t val) { registers[r] = val;}
};
#endif

