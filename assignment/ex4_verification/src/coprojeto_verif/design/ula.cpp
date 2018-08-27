#include "ula.h"

SC_HAS_PROCESS(ula);
ula::ula(sc_module_name nm):
    sc_module   (nm),
    clock       ("clock"),
    in_data_en  ("in_data_en"),
    reset_n     ("reset_n"),
    out_data_rdy("out_data_rdy")
{
  SC_CTHREAD(func,clock.pos());
  async_reset_signal_is(reset_n, false);    
}



void ula::func()
{
  sc_uint<8+1> temp_out_data;
   int temp_sel;
   // reset
   while (true)
   {
      temp_sel = in_sel.read();
      if(reset_n.read() == false) {
   	out_data_rdy.write(0);
   	out_carryout.write(0);
      }
      else if (in_data_en.read() == 1){
	if(in_sel.read() ==  0) {
	  temp_out_data = in_data_a.read() + in_data_b.read();
      	   if (temp_out_data & 0x100) {
          out_carryout.write(1);
        } else {
          out_carryout.write(0);
        }
	}
	else if(in_sel.read() ==  1){ 
	  temp_out_data = in_data_a.read() - in_data_b.read();
      	   if (temp_out_data & 0x100) {
          out_carryout.write(1);
        } else {
          out_carryout.write(0);
        }
	}
	else if(in_sel.read() ==  2){ 
	  temp_out_data = ~in_data_a.read();
      	  out_carryout.write(0);
	}
	else if(in_sel.read() ==  3){ 
	  temp_out_data = in_data_a.read() & in_data_b.read();
      	  out_carryout.write(0);
	}
	else if(in_sel.read() ==  4){ 
	  temp_out_data = in_data_a.read() | in_data_b.read();
      	  out_carryout.write(0);
	}
  else if(in_sel.read() ==  5){ 
     temp_out_data = ~in_data_b.read();
       out_carryout.write(0);
  }
	else if(in_sel.read() ==  6){ 
	  temp_out_data = in_data_a.read() << in_data_b.read();
      	  out_carryout.write(0);
	}
	else if(in_sel.read() ==  7){ 
     temp_out_data = in_data_a.read() ^ in_data_b.read(); 
       out_carryout.write(0);

	}
	else{
	  temp_out_data = 0;
      	  out_carryout.write(0);
	}
	out_data    .write(temp_out_data);
   	out_data_rdy.write(1);
      }
      wait(1);
   }
}
