#include "fir.h"

SC_HAS_PROCESS(fir);
fir::fir(sc_module_name nm_)
	: 	sc_module   (nm_),
  		clock       ("clock"),
  		reset_n     ("reset_n"),
  		in_data_en  ("in_data_en"),
  		out_data_rdy("out_data_rdy")
{
  SC_CTHREAD(func, clock.pos());
  async_reset_signal_is(reset_n, false);
}

void fir::func()
{
	sc_int<8>  sample_tmp;
  	sc_int<17> pro;
  	sc_int<19> acc;
  	sc_int<8> shift[16];

  	for (int i=0; i<=15; i++) 
  		shift[i] = 0;

  	result.write(0);
  	out_data_rdy.write(false);
  	wait();

	while(1) {
		if (reset_n.read() == false) {
			out_data_rdy.write(false);
    	} 
    	else if (in_data_en.read() == 1) {

	    	sample_tmp = sample.read();
	    	acc = sample_tmp*coefs[0];

	    	for(int i=14; i>=0; i--) {
	    		pro = shift[i]*coefs[i+1];
	      		acc += pro;
	    	}

	    	for(int i=14; i>=0; i--) {
	    		shift[i+1] = shift[i];
	    	}

	    	shift[0] = sample_tmp;
	    	result.write((int)acc); 
	    	out_data_rdy.write(true);
	    }
	    wait();
	}
}