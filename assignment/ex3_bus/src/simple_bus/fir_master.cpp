#include "fir_master.h"

void simple_bus_master_blocking::main_action()
{
    int mydata;
    simple_bus_status status;

    const unsigned int mylength     = 1;        // storage capacity/burst length in words
    const unsigned int start        = 0x000;    // base andress for memory 1
    const unsigned int end          = 0xFA0;    // base andress for memory 2
    unsigned int       addr_shift   = 0;        // base offset


    while (true)
    {
        wait(); // ... for the next rising clock edge


        // Read from memory one
        status = bus_port->burst_read(m_unique_priority, (int*)&mydata, 
				    start+addr_shift*4, mylength, m_lock);
        if (status == SIMPLE_BUS_ERROR)
            sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n",
                sc_time_stamp().to_string().c_str(), name(), m_address);

        // Write in memory two
        status = bus_port->burst_write(m_unique_priority, (int*)&mydata, 
				     end+addr_shift*4, mylength, m_lock);

        if (status == SIMPLE_BUS_ERROR)
            sb_fprintf(stdout, "%s %s : blocking-write failed at address %x\n",
		       sc_time_stamp().to_string().c_str(), name(), m_address);

        addr_shift += 1;
        wait(m_timeout, SC_NS);
    }
}
