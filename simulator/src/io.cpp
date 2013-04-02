#include "io.hpp"

void IO::input ()
{
    if (*port == 0) {
        char rslt = getchar();
        *out = (int32_t) rslt;
    } else {
        char filename[15];
        sprintf(filename, "io%010d",*port);
        FILE* fi = fopen(filename, "r");
        if (fi == NULL) {
        }
        fgetc(fi);
        fclose(fi);
    }
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
