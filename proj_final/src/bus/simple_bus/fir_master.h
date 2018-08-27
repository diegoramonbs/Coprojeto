#ifndef __FIR_MASTER_INCLUDED_H__
#define __FIR_MASTER_INCLUDED_H__

#include <systemc.h>

#include "simple_bus_types.h"
#include "simple_bus_blocking_if.h"


SC_MODULE(simple_bus_master_blocking)
{
  // ports
  sc_in_clk clock;
  sc_port<simple_bus_blocking_if> bus_port;

  SC_HAS_PROCESS(simple_bus_master_blocking);

  // constructor
  simple_bus_master_blocking(sc_module_name name_
			     , unsigned int unique_priority
			     , unsigned int address
                             , bool lock
                             , int timeout)
    : sc_module(name_)
    , m_unique_priority(unique_priority)
    , m_address(address)
    , m_lock(lock)
    , m_timeout(timeout)
  {
    // process declaration
    SC_THREAD(main_action);
    sensitive << clock.pos();
  }

  // process
  void main_action();

private:
  unsigned int m_unique_priority;
  unsigned int m_address;
  bool m_lock;
  int m_timeout;

}; // end class simple_bus_master_blocking

#endif
