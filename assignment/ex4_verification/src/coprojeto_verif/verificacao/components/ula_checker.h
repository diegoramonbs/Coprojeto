#ifndef _CHK_H_
#define _CHK_H_

#include <systemc.h>
#include <ula_interface.h>

//+--------------------------------------------------------------------------
//| SC_MODULE: ula_checker
//+--------------------------------------------------------------------------
SC_MODULE(ula_checker)
{
 public:
   sc_in<bool> clk;
   sc_in<bool> clk2;
   sc_in<bool> async_reset;
   
  //-----------------------------
  // TLM Analysis Port
  //-----------------------------
  tlm_analysis_port<ula_sequence_item> chk_port;
  tlm_analysis_port<ula_sequence_item> chk_rm_port;
  tlm_analysis_port<ula_sequence_item> chk_drv_port;

  bool previous_reset;
  bool current_reset;
  bool reset_detected;
  
  int select_checker;

  ula_sequence_item ula_sqi;
  ula_sequence_item ula_drv_sqi;

  ula_subscriber*  ula_dut_sub;
  ula_subscriber*  ula_rm_sub;
  ula_subscriber*  ula_drv_sub;
  
  //-----------------------------
  // Process Declaration
  //-----------------------------
  void check();
  void compare_dut_refmod(ula_sequence_item item);
  void compare_reset(ula_sequence_item item);

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
  
  SC_HAS_PROCESS(ula_checker);
     ula_checker(sc_module_name name): sc_module(name)
  {
    INFO(this->name(), "constructor");
 
    ula_dut_sub = new ula_subscriber("ula_dut_sub");
    chk_port.bind(*ula_dut_sub);
    
    ula_rm_sub = new ula_subscriber("ula_rm_sub");
    chk_rm_port.bind(*ula_rm_sub);
    
    ula_drv_sub = new ula_subscriber("ula_drv_sub");
    chk_drv_port.bind(*ula_drv_sub);
    
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
void ula_checker::check(){
  stringstream msg;

  while(true) {
      ula_sqi = ula_dut_sub->fifo.get();

      if(select_checker == 4){
        ula_checker::compare_reset(ula_sqi);
      }

      if(ula_sqi.data_valid){
    	switch(select_checker){
	  case 1: ula_checker::compare_dut_refmod(ula_sqi); break;
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
void ula_checker::compare_reset(ula_sequence_item item) {
  stringstream msg;

  INFO(name(), "Check reset is active!!!");
  if(!async_reset.read()){

    if(item.data_valid != 0){
      ERROR(name(), "Mismatch o_rdy is not going to zero after reset");
    }

    if(item.data_out != 0){
      ERROR(name(), "Mismatch data_out is not going to zero after reset");
    }

  }
}


//+--------------------------------------------------------------------------
//| FUNCTION: compare_dut_refmod 
//+--------------------------------------------------------------------------
//! Compare output values between reference model and dut
//+--------------------------------------------------------------------------
void ula_checker::compare_dut_refmod(ula_sequence_item item){
  stringstream msg;
  bool find_valid = 0;
  ula_sequence_item ula_rm_sqi;

    while(!find_valid){
      ula_rm_sqi = ula_rm_sub->fifo.get();
      if(ula_rm_sqi.data_valid){
        find_valid = 1;
      }
    }
    find_valid = 0;

    // Estava faltando verificar o carry out

    if(ula_rm_sqi.data_out != item.data_out) {
      msg << "MISMATCH between DUT and Reference Model: data_valid(DUT) = " << ula_sqi.data_out << " - data_valid(DUT) = " << ula_rm_sqi.data_out;
      ERROR(name(), msg.str().c_str());
      msg.str(""); //clean
    }
    if (ula_rm_sqi.carryout != item.carryout) {
      msg << "MISMATCH between DUT and Reference Model: carryout(DUT) = " << ula_sqi.carryout << " - carryout(RM) = " << ula_rm_sqi.carryout;
      ERROR(name(), msg.str().c_str());
      msg.str(""); //clean
    }

    if (ula_rm_sqi.data_out == item.data_out && ula_rm_sqi.carryout == item.carryout) {
      msg << "MATCH between DUT and Reference Model: data_out(DUT) = " << ula_sqi.data_out << " - data_out(RM) = " << ula_rm_sqi.data_out;
      INFO(name(), msg.str().c_str(), HIGH);
      msg.str(""); //clean
      msg << "MATCH between DUT and Reference Model: carryout(DUT) = " << ula_sqi.carryout << " - carryout(RM) = " << ula_rm_sqi.carryout;
      INFO(name(), msg.str().c_str(), HIGH);
      msg.str(""); //clean
  } 
}

#endif /* VIP_SC_CHK_H_ */
