#ifndef _ALU
#define _ALU
class ALU {
    private:
        int* in1;
        int* in2;
        int* out;

        int* flag_z;
        int* flag_p;
        int* flag_n;

        void do_add ();
        void do_sub ();
        void do_and ();
        void do_or ();
        void do_xor ();
        void do_sr ();
        void do_sl ();
    public:
        void do_op (int op);
};
#endif

