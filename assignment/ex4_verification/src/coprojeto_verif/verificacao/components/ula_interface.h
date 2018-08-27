// interface definitions for VIP

#ifndef _IF_H_
#define _IF_H_

#include <systemc>

class ula_interface
{

 public:
 
  sc_signal<bool>       in_data_en;    
  sc_signal<dut_data_t> in_data_a; 
  sc_signal<dut_data_t> in_data_b; 
  sc_signal<dut_sel_t>  in_sel;    
  
  sc_signal<dut_data_t> out_data;    
  sc_signal<bool>       out_carryout; 
  sc_signal<bool>       out_data_rdy; 


   ula_interface(){}
   ~ula_interface(){}
};


#endif /* _IF_H_ */
