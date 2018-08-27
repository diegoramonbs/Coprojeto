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

#include "ula_interface.h"
#include "ula_define.h"

//-----------------------------
// Constants
//-----------------------------


SC_MODULE(ula_monitor)
{
    //-----------------------------
    // Input
    //-----------------------------
    sc_in<bool> clk;
    sc_in<bool> async_reset;

    ula_interface* ula_if;
    ula_sequence_item* ula_sqi;
    ula_sequence_item* ula_sqi_clone;

    int monitor_errors;
    string fname_data_out;
    ofstream file_data_out;

    //-----------------------------
    // TLM Analysis Port
    //-----------------------------
    tlm_analysis_port<ula_sequence_item> mon_port;

    //-----------------------------
    // Process Declaration
    //-----------------------------
    void capture_signals();
    void copy_if_sqi();

    //-----------------------------
    // Constructor
    //-----------------------------
    SC_HAS_PROCESS(ula_monitor);
    ula_monitor(sc_module_name name, ula_interface* sc_if) : sc_module(name)
    {

        INFO(this->name(), "construtor");
        const char *c = name;
        string n(c);
        monitor_errors = 0;
        fname_data_out = result_path + n + "_output.txt";
        file_data_out.open (fname_data_out.c_str(), ofstream::out);

        ula_sqi = new ula_sequence_item("ula_sqi");
        ula_sqi_clone = new ula_sequence_item("ula_sqi_clone"); //Necessary to avoid overwrite
	
	ula_if = sc_if;
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
void ula_monitor::capture_signals(){
  stringstream msg;  
  while (true) {
    if(!async_reset.read()){
      wait(1, ASYNC_RST_TIMEUNIT);
    }
    ula_monitor::copy_if_sqi();
    ula_sqi_clone = ula_sqi;
    mon_port.write(*ula_sqi_clone);
    wait(1); 
  }
}

//+--------------------------------------------------------------------------
//| FUNCTION: copy_if_sqi
//+--------------------------------------------------------------------------
//! Copy interface signals to sequence item
//+--------------------------------------------------------------------------
void ula_monitor::copy_if_sqi(){
  ula_sqi->data_valid  = ula_if->out_data_rdy.read();
  ula_sqi->data_out    = ula_if->out_data.read();
  ula_sqi->carryout    = ula_if->out_carryout.read();


  //save output data 
  file_data_out << ula_if->out_data_rdy << " " << ula_if->out_data << " " << ula_if->out_carryout << endl;
}

#endif
