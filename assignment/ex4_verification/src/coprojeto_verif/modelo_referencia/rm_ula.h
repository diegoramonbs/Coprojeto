#define SC_INCLUDE_FX

#include "systemc.h"

#define NBITS_SIZE 8

//Signals typedef used for input and output
typedef sc_uint<NBITS_SIZE> data_t;
typedef sc_uint<3> sel_t;

SC_MODULE(rm_ula)
{
  sc_in<bool> clock;
  sc_in<bool> reset_n; //Rest enable at negative edge

  sc_in<bool>   in_data_en; //Flag to say that in_data_a and in_data_b is valid
  sc_in<data_t> in_data_a;  //Data input
  sc_in<data_t> in_data_b;  //Data input
  sc_in<sel_t>  in_sel;     //select the operation
  
  sc_out<data_t> out_data;     //Data output
  sc_out<bool>   out_carryout; //Carry out flag
  sc_out<bool>   out_data_rdy; //Flag to say that the out_data is valid
  void func();
  
  rm_ula(sc_module_name nm);

}; // end of SC_MODULE

