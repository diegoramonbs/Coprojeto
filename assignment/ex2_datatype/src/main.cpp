#include "systemc.h"
#include "stim.h"
#include "mon.h"
#include "adder.h"
#include "multi.h"

int sc_main (int argc, char* argv[])
{
    sc_signal < sc_uint<64> > As, Bs, Sums, Muls;
    sc_clock TestClk ("TestClock", 10, SC_NS, 0.5);
    
    stim Stimulus ("Stimulus");
    Stimulus.A (As); Stimulus.B (Bs); Stimulus.Clock (TestClk);
    
    adder AdderDUT ("Adder");
    AdderDUT.A (As); AdderDUT.B (Bs); AdderDUT.S (Sums); 
    
    multi MultiDUT ("Multi");
    MultiDUT.A (Sums); MultiDUT.B (Bs); MultiDUT.M (Muls);
    
    mon Monitor ("Monitor");
    Monitor.A (As); Monitor.B (Bs); Monitor.Sum (Sums); Monitor.Mul (Muls); Monitor.Clock (TestClk);
    
    sc_start();
    return 0;
}
