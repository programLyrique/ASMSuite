#ifndef _ALU
#define _ALU
#include <cstdint>

//Pas de define de constante en C++ !
//#define ADD 0
//#define SUB 1
//#define AND 2
//#define OR 3
//#define XOR 4
//#define SR 5
//#define SL 6

using namespace std;

namespace operation
{

    enum OPE
    {
        ADD,
        SUB,
        AND,
        OR,
        XOR,
        SR,
        SL
    };
}

class ALU
{
private:
    int32_t* in1;
    int32_t* in2;
    int32_t* out;

    bool* flag_z;
    bool* flag_p;
    bool* flag_n;

    void do_add();
    void do_sub();
    void do_and();
    void do_or();
    void do_xor();
    void do_sr();
    void do_sl();
public:
    ALU(int32_t* _in1, int32_t* _in2, int32_t* _out, bool* _flag_z,
        bool* _flag_p, bool* _flag_n);
    void do_op(int op);
};
#endif

