#include <report_server.h>

#define FIR_SEED          1
#define FIR_TIMEOUT       2000
#define FIR_TIMEUNIT      SC_NS

#define DATA_NUMBER_BITS  8
#define SEL_NUMBER_BITS   3 

#ifndef  FIR_TEST_CONFIG
#define FIR_TEST_CONFIG
  struct test_config {
    int          NI; // Number of interactions
    unsigned int seed; //Seed used in randomization and PRBS
    string testname; 
  };
#endif

typedef int dut_data_t;


