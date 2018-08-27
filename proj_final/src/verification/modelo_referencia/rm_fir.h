#define SC_INCLUDE_FX

#include <systemc.h>

SC_MODULE(rm_fir)
{
	sc_in<bool> 	clock;
	sc_in<bool> 	reset_n;
	sc_in<bool> 	in_data_en;
	sc_out<bool>   	out_data_rdy;
	sc_in<int>  	sample;
	sc_out<int> 	result;

	sc_int<9>		coefs[16];

	void func();
	rm_fir(sc_module_name nm_);
	
};
