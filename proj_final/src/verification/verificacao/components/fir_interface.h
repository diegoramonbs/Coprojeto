// interface definitions for VIP

#ifndef _IF_H_
#define _IF_H_

#include <systemc>

class fir_interface
{

 public:
 
  sc_signal<bool>       in_data_en;    
  sc_signal<dut_data_t> sample;   
  
  sc_signal<dut_data_t> result;    
  sc_signal<bool>       out_data_rdy; 


   fir_interface(){}
   ~fir_interface(){}
};


#endif /* _IF_H_ */
