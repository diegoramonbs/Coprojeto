#include <systemc.h>
#include <assert.h>
#include <fir_driver.h>
#include <fir_sequence_item.h>


//+--------------------------------------------------------------------------
//| FUNCTION: randomize
//+--------------------------------------------------------------------------
//! Generate a randomize data 
//+--------------------------------------------------------------------------
void fir_driver::randomize()
{
  stringstream msg;
  fir_sqi->data_enable = 1;
  fir_sqi->sample = rand() % 256;    
  msg << "Generate: sample = " << fir_sqi->sample;
  INFO(name(), msg.str().c_str(), HIGH);
  msg.str(""); //clean

  update_interface = 1;
  wait(1);
}
 
//+--------------------------------------------------------------------------
//| FUNCTION: set_data
//+--------------------------------------------------------------------------
//! Receive a double data and passe to in_data_a and in_data_b 
//+--------------------------------------------------------------------------
void fir_driver::set_data(double data_a )
{
  stringstream msg;
  fir_sqi->data_enable = 1;

  fir_sqi->sample = data_a;
 
  update_interface = 1;
}
