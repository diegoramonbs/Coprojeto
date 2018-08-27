#ifndef __MUL_HPP__
#define __MUL_HPP__ 

#include "systemc.h"

SC_MODULE (multi) 
{
    sc_in< sc_uint<64> > A, B;
    sc_out< sc_uint<64> > M;
    
    void mul() 
    {
        M.write (A.read() * B.read());
    }

    SC_CTOR (multi) 
    {
        SC_METHOD (mul);
        sensitive << A << B;
    }     
};




#endif
