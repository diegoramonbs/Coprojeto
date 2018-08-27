#ifndef _MON_HPP_
#define _MON_HPP_

#include "systemc.h"
#include <iomanip>
using namespace std;

SC_MODULE (mon) {
    sc_in< sc_uint<64> > A, B, Sum, Mul;
    sc_in<bool> Clock;
    
    void monitor() {
        cout << setw (12) << "Time";
        cout << setw (12) << "A";
        cout << setw (12) << "B";
        cout << setw (12) << "Sum";
        cout << setw (12) << "Mul" << endl;
        
        while (true) {
            cout << setw (12) << sc_time_stamp();
            cout << setw (12) << A.read();
            cout << setw (12) << B.read();
            cout << setw (12) << Sum.read();
            cout << setw (12) << Mul.read() << endl;
            wait();
        }
    }

    SC_CTOR (mon) {
        SC_THREAD (monitor);
        sensitive << Clock.pos();
    }      
};


#endif
