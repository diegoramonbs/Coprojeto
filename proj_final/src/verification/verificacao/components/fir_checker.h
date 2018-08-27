#ifndef _CHK_H_
#define _CHK_H_

#include <systemc.h>
#include <fir_interface.h>

//+--------------------------------------------------------------------------
//| SC_MODULE: fir_checker
//+--------------------------------------------------------------------------
SC_MODULE(fir_checker)
{
 public:
   sc_in<bool> clk;
   sc_in<bool> clk2;
   sc_in<bool> async_reset;
   
  //-----------------------------
  // TLM Analysis Port
  //-----------------------------
  tlm_analysis_port<fir_sequence_item> chk_port;
  tlm_analysis_port<fir_sequence_item> chk_rm_port;
  tlm_analysis_port<fir_sequence_item> chk_drv_port;

  bool previous_reset;
  bool current_reset;
  bool reset_detected;
  
  int select_checker;

  fir_sequence_item fir_sqi;
  fir_sequence_item fir_drv_sqi;

  fir_subscriber*  fir_dut_sub;
  fir_subscriber*  fir_rm_sub;
  fir_subscriber*  fir_drv_sub;
  
  //-----------------------------
  // Process Declaration
  //-----------------------------
  void check();
  void compare_dut_refmod(fir_sequence_item item);
  void compare_reset(fir_sequence_item item);

  //+--------------------------------------------------------------------------
  //| FUNCTION: is_close_out
  //+--------------------------------------------------------------------------
  bool is_close_out(double x1, double x2,  double tol = exp2(-7)/*1e-10*/){
    bool rv;
    rv = abs(x1-x2)<tol;
    return rv;
  }
  
  //+--------------------------------------------------------------------------
  //| FUNCTION: is_close_in
  //+--------------------------------------------------------------------------
  bool is_close_in(double x1, double x2,  double tol = exp2(-7)/*1e-10*/){
    bool rv;
    rv = abs(x1-x2)<tol;
    return rv;
  }
  
  SC_HAS_PROCESS(fir_checker);
     fir_checker(sc_module_name name): sc_module(name)
  {
    INFO(this->name(), "constructor");
 
    fir_dut_sub = new fir_subscriber("fir_dut_sub");
    chk_port.bind(*fir_dut_sub);
    
    fir_rm_sub = new fir_subscriber("fir_rm_sub");
    chk_rm_port.bind(*fir_rm_sub);
    
    fir_drv_sub = new fir_subscriber("fir_drv_sub");
    chk_drv_port.bind(*fir_drv_sub);
    
    select_checker = 0;
    previous_reset = 1;
    reset_detected = 0;  

    SC_THREAD(check)
       sensitive << clk.pos();
       async_reset_signal_is(async_reset, false); 
  }
};

//+--------------------------------------------------------------------------
//| FUNCTION: check 
//+--------------------------------------------------------------------------
//! Wait to receive a valid clock, and call the function which compare the 
//! input data with the output data. 
//+--------------------------------------------------------------------------
void fir_checker::check(){
  stringstream msg;

  while(true) {
      fir_sqi = fir_dut_sub->fifo.get();

      if(select_checker == 4){
        fir_checker::compare_reset(fir_sqi);
      }

      if(fir_sqi.data_valid){
    	switch(select_checker){
	  case 1: fir_checker::compare_dut_refmod(fir_sqi); break;
          default: break;
    	}
      }
    wait(1); 
  }
}

//+--------------------------------------------------------------------------
//| FUNCTION: compare_reset
//+--------------------------------------------------------------------------
//! Check reset values on dut outputs
//+--------------------------------------------------------------------------
void fir_checker::compare_reset(fir_sequence_item item) {
  stringstream msg;

  INFO(name(), "Check reset is active!!!");
  if(!async_reset.read()){

    if(item.data_valid != 0){
      ERROR(name(), "Mismatch o_rdy is not going to zero after reset");
    }

    if(item.result != 0){
      ERROR(name(), "Mismatch result is not going to zero after reset");
    }

  }
}


//+--------------------------------------------------------------------------
//| FUNCTION: compare_dut_refmod 
//+--------------------------------------------------------------------------
//! Compare output values between reference model and dut
//+--------------------------------------------------------------------------
void fir_checker::compare_dut_refmod(fir_sequence_item item){
  stringstream msg;
  bool find_valid = 0;
  fir_sequence_item fir_rm_sqi;

    while(!find_valid){
      fir_rm_sqi = fir_rm_sub->fifo.get();
      if(fir_rm_sqi.data_valid){
        find_valid = 1;
      }
    }
    find_valid = 0;

    if(fir_rm_sqi.result != item.result) {
      msg << "MISMATCH between DUT and Reference Model: data_valid(DUT) = " << fir_sqi.result << " - data_valid(DUT) = " << fir_rm_sqi.result;
      ERROR(name(), msg.str().c_str());
      msg.str(""); //clean
    }
    else {
      msg << "MATCH between DUT and Reference Model:data_valid(DUT) = " << fir_sqi.result << " - data_valid(DUT) = " << fir_rm_sqi.result;
      INFO(name(), msg.str().c_str(), HIGH);
      msg.str(""); //clean
    }
    
}

#endif /* VIP_SC_CHK_H_ */
