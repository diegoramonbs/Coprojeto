#include <report_server.h>

#define ULA_SEED          1
#define ULA_TIMEOUT       50000  // O tempo estava insuficiente
#define ULA_TIMEUNIT      SC_NS

#define DATA_NUMBER_BITS  8
#define SEL_NUMBER_BITS   3 

#ifndef  ULA_TEST_CONFIG
#define ULA_TEST_CONFIG
  struct test_config {
    int          NI; // Number of interactions
    unsigned int seed; //Seed used in randomization and PRBS
    string testname; 
  };
#endif

typedef sc_uint<DATA_NUMBER_BITS> dut_data_t;
typedef sc_uint<SEL_NUMBER_BITS>  dut_sel_t;

