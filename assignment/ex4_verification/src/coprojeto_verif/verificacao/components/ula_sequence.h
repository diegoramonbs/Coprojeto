#include <systemc.h>
#include <assert.h>
#include <ula_driver.h>
#include <ula_sequence_item.h>


//+--------------------------------------------------------------------------
//| FUNCTION: randomize
//+--------------------------------------------------------------------------
//! Generate a randomize data 
//+--------------------------------------------------------------------------
void ula_driver::randomize()
{
  stringstream msg;
  ula_sqi->data_enable = 1;
  ula_sqi->data_a = rand() % 256;    
  ula_sqi->data_b = rand() % 256;    
  ula_sqi->sel    = rand() % 8;    
  msg << "Generate: data_a = " << ula_sqi->data_a << "| data_b = " << ula_sqi->data_b << "| sel = " << ula_sqi->sel;
  INFO(name(), msg.str().c_str(), HIGH);
  msg.str(""); //clean

  update_interface = 1;
  wait(1);
}


//+--------------------------------------------------------------------------
//| FUNCTION: randomize
//+--------------------------------------------------------------------------
//! Generate a randomize data 
//+--------------------------------------------------------------------------
void ula_driver::randomize( int sel )
{
  stringstream msg;
  ula_sqi->data_enable = 1;
  ula_sqi->data_a = rand() % 256;    
  ula_sqi->data_b = rand() % 256;    
  ula_sqi->sel    = sel; 
  msg << "Generate: data_a = " << ula_sqi->data_a << "| data_b = " << ula_sqi->data_b << "| sel = " << ula_sqi->sel;
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
void ula_driver::set_data(double data_a, double data_b)
{
  stringstream msg;
  ula_sqi->data_enable = 1;

  ula_sqi->data_a = data_a;
  ula_sqi->data_b = data_b;
 
  update_interface = 1;
}

//+--------------------------------------------------------------------------
//| FUNCTION: set_sel
//+--------------------------------------------------------------------------
//! Receive a int data and passe to in_sel
//+--------------------------------------------------------------------------
void ula_driver::set_sel(int sel)
{
  stringstream msg;
  ula_sqi->sel = sel;

  update_interface = 1;
}
