
#ifndef _DRV_H_
#define _DRV_H_

//-----------------------------
// SystemC defines and includes
//-----------------------------
#include "systemc.h"
#include "tlm.h"
using namespace std;
using namespace tlm;

#include <ula_interface.h>
#include <ula_rst_interface.h>
#include <ula_sequence_item.h>

SC_MODULE(ula_driver)
{

    //-----------------------------
    // Input
    //-----------------------------
    sc_in<bool> clk;
    sc_in<bool> async_reset;

    ula_interface* drv_if;
  
    //Sequence item
    ula_sequence_item* ula_sqi;
 
    int driver_errors;
    
    string fname_h;
    ofstream file_h;
    
    bool update_interface;

    //-----------------------------
    // TLM Analysis Port
    //-----------------------------
    tlm_analysis_port<ula_sequence_item> drv_port;

    //-----------------------------
    // Process Declaration
    //-----------------------------
    void drive();
    void set_seed(int new_seed);
    void set_data(double , double);
    void set_sel(int);
    void randomize();
    void randomize(int);

    SC_HAS_PROCESS(ula_driver);
     ula_driver(sc_module_name name, ula_interface* in_if)
   : sc_module(name),clk("clk"),async_reset("async_reset")
    {
        INFO(this->name(), "construtor");

        driver_errors = 0;
	update_interface = 0;
        fname_h = result_path + "ula_input.txt";
        file_h.open (fname_h.c_str(), ofstream::out);

  	ula_sqi = new ula_sequence_item("ula_sqi");

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
void ula_driver::set_seed(int new_seed)
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
void ula_driver::drive()
{
  stringstream msg;
  bool current_reset;

  while(true){
    current_reset = async_reset.read(); 
    if(current_reset == 0) {
      drv_if->in_data_en.write(0);
      drv_if->in_data_a .write(0);
      drv_if->in_data_b .write(0);
      drv_if->in_sel    .write(0);
    }
    else if(update_interface == 1){
      //Drive into drive's interface
      drv_if->in_data_en.write(ula_sqi->data_enable);

      drv_if->in_data_a .write(ula_sqi->data_a);     
      drv_if->in_data_b .write(ula_sqi->data_b);
      drv_if->in_sel    .write(ula_sqi->sel);

      //save drive at each clock
      file_h << drv_if->in_data_en << " " <<  drv_if->in_data_a << " " << drv_if->in_data_b << " " << drv_if->in_sel << endl;

      //send the data to checker
      drv_port.write(*ula_sqi);
      update_interface = 0;
    }   
    wait(1);
  }
}


#endif
