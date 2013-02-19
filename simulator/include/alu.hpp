#ifndef _ALU
#define _ALU
#include <cstdint>

using namespace std;

class ALU {
    private:
        int32_t* in1;
        int32_t* in2;
        int32_t* out;

        int32_t* flag_z;
        int32_t* flag_p;
        int32_t* flag_n;

        void do_add ();
        void do_sub ();
        void do_and ();
        void do_or ();
        void do_xor ();
        void do_sr ();
        void do_sl ();
    public:
        ALU(int32_t* _in1, int32_t* _in2, int32_t* _out, int32_t* _flag_z,
            int32_t* _flag_p, int32_t* _flag_n);
        void do_op (int op);
};
#endif

