#include "fir_master.h"

void simple_bus_master_blocking::main_action()
{
    int mydata;
    simple_bus_status status;

    const unsigned int mylength     = 1;        // storage capacity/burst length in words
    const unsigned int start        = 0;        // base andress for memory 1
    const unsigned int end          = 40;       // base andress for memory 2
    unsigned int       addr_shift   = 0;        // base offset

    sc_int<8>   sample_tmp;
    sc_int<17>  pro;
    sc_int<19>  acc;
    sc_int<8>   shift[16];
    sc_int<9>   coefs[16];

    coefs[0] = -6;
    coefs[1] = -4;
    coefs[2] = 13;
    coefs[3] = 16;
    coefs[4] = -18;
    coefs[5] = -41;
    coefs[6] = 23;
    coefs[7] = 154;
    coefs[8] = 222;
    coefs[9] = 154;
    coefs[10] = 23;
    coefs[11] = -41;
    coefs[12] = -18;
    coefs[13] = 16;
    coefs[14] = 13; 
    coefs[15] = -4;

    while (true)
    {
        wait(); // ... for the next rising clock edge


        // Read from memory one
        status = bus_port->burst_read(m_unique_priority, (int*)&mydata, 
				    start+addr_shift*4, mylength, m_lock);
        if (status == SIMPLE_BUS_ERROR)
            sb_fprintf(stdout, "%s %s : blocking-read failed at address %x\n",
                sc_time_stamp().to_string().c_str(), name(), m_address);

        for (int i=0; i<=15; i++) 
            shift[i] = 0;

        sample_tmp = mydata;
        acc = sample_tmp*coefs[0];
        for(int i=14; i>=0; i--) 
        {
            pro = shift[i]*coefs[i+1];
            acc += pro;
        }

        for(int i=14; i>=0; i--) 
        {
            shift[i+1] = shift[i];
        }

        shift[0] = sample_tmp;
        mydata = (int)acc; 

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
