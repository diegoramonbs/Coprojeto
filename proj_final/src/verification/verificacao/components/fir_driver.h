
#ifndef _DRV_H_
#define _DRV_H_

//-----------------------------
// SystemC defines and includes
//-----------------------------
#include "systemc.h"
#include "tlm.h"
using namespace std;
using namespace tlm;

#include <fir_interface.h>
#include <fir_rst_interface.h>
#include <fir_sequence_item.h>

SC_MODULE(fir_driver)
{

    //-----------------------------
    // Input
    //-----------------------------
    sc_in<bool> clk;
    sc_in<bool> async_reset;

    fir_interface* drv_if;
  
    //Sequence item
    fir_sequence_item* fir_sqi;
 
    int driver_errors;
    
    string fname_h;
    ofstream file_h;
    
    bool update_interface;

    //-----------------------------
    // TLM Analysis Port
    //-----------------------------
    tlm_analysis_port<fir_sequence_item> drv_port;

    //-----------------------------
    // Process Declaration
    //-----------------------------
    void drive();
    void set_seed(int new_seed);
    void set_data(double);

    void randomize();

    SC_HAS_PROCESS(fir_driver);
     fir_driver(sc_module_name name, fir_interface* in_if)
   : sc_module(name),clk("clk"),async_reset("async_reset")
    {
        INFO(this->name(), "construtor");

        driver_errors = 0;
	update_interface = 0;
        fname_h = result_path + "fir_input.txt";
        file_h.open (fname_h.c_str(), ofstream::out);

  	fir_sqi = new fir_sequence_item("fir_sqi");

  	drv_if = in_if;

        srand(0);
        //----------------------------
        // Process registration
        //----------------------------
        SC_CTHREAD(drive,clk.pos());
          async_reset_signal_is(async_reset, false); 
	  
    }
     
};

//+--------------------------------------------------------------------------
//| FUNCTION: set_seed
//+--------------------------------------------------------------------------
//! This function randomize with
//! the seed that is put by prompt
//+--------------------------------------------------------------------------
void fir_driver::set_seed(int new_seed)
{
   srand(new_seed);
   update_interface = 1;
}

//+--------------------------------------------------------------------------
//| FUNCTION: drive
//+--------------------------------------------------------------------------
//! Get the data from the sequece item and drive in the DUT. Put the sequence
//! item used to a TLM port to be used in the bypass mode checker.
//+--------------------------------------------------------------------------
void fir_driver::drive()
{
  stringstream msg;
  bool current_reset;

  while(true){
    current_reset = async_reset.read(); 
    if(current_reset == 0) {
      drv_if->in_data_en.write(0);
      drv_if->sample .write(0);
    
    }
    else if(update_interface == 1){
      //Drive into drive's interface
      drv_if->in_data_en.write(fir_sqi->data_enable);

      drv_if->sample.write(fir_sqi->sample);     
      

      //save drive at each clock
      file_h << drv_if->in_data_en << " " <<  drv_if->sample << " " << endl;

      //send the data to checker
      drv_port.write(*fir_sqi);
      update_interface = 0;
    }   
    wait(1);
  }
}


#endif
