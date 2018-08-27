#ifndef _MON_H_
#define _MON_H_

//-----------------------------
// SystemC defines and includes
//-----------------------------
#include "systemc.h"
#include <string>
#include "tlm.h"

using namespace std;
using namespace tlm;

#include "fir_interface.h"
#include "fir_define.h"

//-----------------------------
// Constants
//-----------------------------


SC_MODULE(fir_monitor)
{
    //-----------------------------
    // Input
    //-----------------------------
    sc_in<bool> clk;
    sc_in<bool> async_reset;

    fir_interface* fir_if;
    fir_sequence_item* fir_sqi;
    fir_sequence_item* fir_sqi_clone;

    int monitor_errors;
    string fname_data_out;
    ofstream file_data_out;

    //-----------------------------
    // TLM Analysis Port
    //-----------------------------
    tlm_analysis_port<fir_sequence_item> mon_port;

    //-----------------------------
    // Process Declaration
    //-----------------------------
    void capture_signals();
    void copy_if_sqi();

    //-----------------------------
    // Constructor
    //-----------------------------
    SC_HAS_PROCESS(fir_monitor);
    fir_monitor(sc_module_name name, fir_interface* sc_if) : sc_module(name)
    {

        INFO(this->name(), "construtor");
        const char *c = name;
        string n(c);
        monitor_errors = 0;
        fname_data_out = result_path + n + "_output.txt";
        file_data_out.open (fname_data_out.c_str(), ofstream::out);

        fir_sqi = new fir_sequence_item("fir_sqi");
        fir_sqi_clone = new fir_sequence_item("fir_sqi_clone"); //Necessary to avoid overwrite
	
	fir_if = sc_if;
        //----------------------------
        // Process registration
        //----------------------------

        SC_THREAD(capture_signals);
           sensitive <<  async_reset.neg() << clk.pos();
    }
};

//+--------------------------------------------------------------------------
//| FUNCTION: capture_signals
//+--------------------------------------------------------------------------
//! Check if reset happens, copy the DUT interface to a sequence item and 
//! write it in the TLM port.
//+--------------------------------------------------------------------------
void fir_monitor::capture_signals(){
  stringstream msg;  
  while (true) {
    if(!async_reset.read()){
      wait(1, ASYNC_RST_TIMEUNIT);
    }
    fir_monitor::copy_if_sqi();
    fir_sqi_clone = fir_sqi;
    mon_port.write(*fir_sqi_clone);
    wait(1); 
  }
}

//+--------------------------------------------------------------------------
//| FUNCTION: copy_if_sqi
//+--------------------------------------------------------------------------
//! Copy interface signals to sequence item
//+--------------------------------------------------------------------------
void fir_monitor::copy_if_sqi(){
  fir_sqi->data_valid  = fir_if->out_data_rdy.read();
  fir_sqi->result    = fir_if->result.read();


  //save output data 
  file_data_out << fir_if->out_data_rdy << " " << fir_if->result << " " << endl;
}

#endif
