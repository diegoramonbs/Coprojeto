#ifndef __STIM_HPP__
#define __STIM_HPP__ 

#include "systemc.h"
#include <stdlib.h>

const int RANGE = 16;

SC_MODULE (stim) 
{
    sc_out< sc_uint<64> > A, B;
    sc_in<bool> Clock;
    
    void stimGen() 
    {
        wait();
        for (int i = 0; i < RANGE; i++) 
        {
            A.write (rand() % RANGE);
            B.write (rand() % RANGE);
            wait();
        }
        sc_stop();
    }

    SC_CTOR (stim) 
    {
        SC_THREAD (stimGen);
        sensitive << Clock.pos();
    }
};

#endif
