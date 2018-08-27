#ifndef __swap_h
#define __swap_h

#include <systemc.h>

#include "simple_bus/fir_master.h"
#include "simple_bus/simple_bus_slow_mem.h"
#include "simple_bus/simple_bus.h"
#include "simple_bus/simple_bus_arbiter.h"

SC_MODULE(swap)
{
  // channels
  sc_clock C1;

  // module instances
  simple_bus_master_blocking     *master_b;
  simple_bus_slow_mem            *mem_slow1;
  simple_bus_slow_mem            *mem_slow2;
  simple_bus                     *bus;
  simple_bus_arbiter             *arbiter;

  // constructor
  SC_CTOR(swap)
    : C1("C1")
  {
    // create instances
    master_b = new simple_bus_master_blocking("master_b", 4, 0x4c, false, 300);
    mem_slow1 = new simple_bus_slow_mem("mem_slow1", 0, 39, 1);
    mem_slow2 = new simple_bus_slow_mem("mem_slow2", 40, 79, 1);
    bus = new simple_bus("bus");
    arbiter = new simple_bus_arbiter("arbiter");

    // connect instances
    bus->clock(C1);
    master_b->clock(C1);
    mem_slow1->clock(C1);
    mem_slow2->clock(C1);
    master_b->bus_port(*bus);
    bus->arbiter_port(*arbiter);
    bus->slave_port(*mem_slow1);
    bus->slave_port(*mem_slow2);

    // Initialize the first slow memory with random samples
    int data;
    unsigned int addr = 0x00;
    for( int i = 0; i < 10; i++)
    {
      data = rand() % 256;
      mem_slow1->direct_write(&data, addr);
      addr += 4;
    }
  }

  // destructor
  ~swap()
  {
    //Show the data final in memory
    mem_slow1->dump();
    mem_slow2->dump();

    if (master_b) {delete master_b; master_b = 0;}
    if (mem_slow1) {delete mem_slow1; mem_slow1 = 0;}
    if (mem_slow2) {delete mem_slow2; mem_slow2 = 0;}
    if (bus) {delete bus; bus = 0;}
    if (arbiter) {delete arbiter; arbiter = 0;}
  }

}; // end class simple_bus_test

#endif
