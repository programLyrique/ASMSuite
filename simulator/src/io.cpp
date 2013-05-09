#include "io.hpp"

#include <iostream>

void IO::input ()
{
    char rslt;
    if (*port == 0) {
        rslt = getchar();
    } else {
        char filename[15];
        sprintf(filename, "io%010d",*port);
        FILE* fi = fopen(filename, "r");
        if (fi == NULL) {
            std::cerr << "Impossible d'accéder au port." <<std::endl;
        }
        rslt =  fgetc(fi);
        fclose(fi);
    }
    *out = (int32_t) rslt;
}

void IO::output ()
{
    char out_char;
    int32_t mask = 255;
    out_char = (char) ((*in) & mask);
    if (*port == 0) {
        putchar(out_char);
    } else {
        char filename[15];
        sprintf(filename, "io%010d",*port);
        FILE* fi = fopen(filename, "a");
        fputc(out_char, fi);
        fclose(fi);
    }
}
