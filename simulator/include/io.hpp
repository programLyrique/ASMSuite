#ifndef _IO
#define _IO
#include <cstdint>
#include <cstdio>


//Pas de define en C++ de constantes !!
//#define IN 0
//#define OUT 1

namespace io_op
{

    enum IO_OP
    {
        IN,
        OUT
    };
}

class IO
{
private:
    int32_t* in;
    int32_t* out;
    int32_t* port;
public:

    IO(int32_t* _in, int32_t* _out, int32_t* _port)
    {
        in = _in;
        out = _out;
        port = _port;
    }
    void input();
    void output();
};

#endif

