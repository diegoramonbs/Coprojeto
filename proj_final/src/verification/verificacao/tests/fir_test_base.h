#include <fir_define.h>
#include <fir_sequence.h>
#include <fir_environment.h>

//+--------------------------------------------------------------------------
//| CLASS: fir_test_base
//+--------------------------------------------------------------------------
class fir_test_base {

  public :
    //+--------------------------------------------------------------------------
    //| Data Members
    //+--------------------------------------------------------------------------
    const char*  name;
    int          NI; // Number of interactions
    unsigned int seed; //Seed used in randomization and PRBS
    string testname;

    //+--------------------------------------------------------------------------
    //| Components Members
    //+--------------------------------------------------------------------------
    fir_environment* fir_env;
    
    //+--------------------------------------------------------------------------
    //| FUNCTION: constructor
    //+--------------------------------------------------------------------------
    fir_test_base(const char* _name,
                     fir_rst_interface* sc_rst_if,
                     fir_interface*     test_sc_if,
                     fir_interface*     rm_test_sc_if,
		     test_config*       tst_cfg){
      INFO(_name, "Constructor", MEDIUM);
      fir_env = new fir_environment("fir_env", sc_rst_if, test_sc_if, rm_test_sc_if);
      name = _name;
      testname = tst_cfg->testname;
      NI   = tst_cfg->NI;
      seed = tst_cfg->seed;
      srand(seed);
    }

    //+--------------------------------------------------------------------------
    //| FUNCTION: reset_phase
    //+--------------------------------------------------------------------------
    //! Virtual Function to implementation of reset phase
    //+--------------------------------------------------------------------------
    virtual void reset_phase(){
      INFO(name, "Start Reset Phase", MEDIUM);
      fir_env->fir_reset->async_reset();
      fir_env->fir_reset->wait_posedge(10); 
    }

   //+--------------------------------------------------------------------------
    //| FUNCTION: configure_phase
    //+--------------------------------------------------------------------------
    //! Virtual Function to implementation of configure phase
    //+--------------------------------------------------------------------------    
    virtual void configure_phase(){
    }

    //+--------------------------------------------------------------------------
    //| FUNCTION: run_phase
    //+--------------------------------------------------------------------------
    //! Virtual Function to implementation of run phase
    //+--------------------------------------------------------------------------
    virtual void run_phase(){
      INFO(name, "Start Run Phase", MEDIUM);
    }
    
    //+--------------------------------------------------------------------------
    //| FUNCTION: end_of_run_phase
    //+--------------------------------------------------------------------------
    //! Virtual Function to wait time to end of simfirtion
    //+--------------------------------------------------------------------------
    virtual void end_of_run_phase(){
      fir_env->fir_reset->wait_posedge(100); 
    }

    //+--------------------------------------------------------------------------
    //| FUNCTION: report_phase
    //+--------------------------------------------------------------------------
    //! Virtual Function to show the result of simfirtion
    //+--------------------------------------------------------------------------    
    virtual void report_phase() {
      stringstream msg;
      int errors;

      //Get errors from server
      errors = report_server::report::get_errors();

      if(errors) {      
        INFO(name, "                                          ", LOW);
        INFO(name, "#########   #######   #########  ##       ", LOW);
        INFO(name, "##         ##     ##     ##      ##       ", LOW);
        INFO(name, "##         ##     ##     ##      ##       ", LOW);
        INFO(name, "######     #########     ##      ##       ", LOW);
        INFO(name, "##         ##     ##     ##      ##       ", LOW);
        INFO(name, "##         ##     ##     ##      ##       ", LOW);
        INFO(name, "##         ##     ##  #########   ########", LOW);
        INFO(name, "                                          ", LOW);
	msg << "Simfirtion completed with " << errors << " errors!";
        ERROR(name, msg.str().c_str(), LOW);
      }
      else {
        INFO(name, "                                          ", LOW);
        INFO(name, "########    #######     ######     ###### ", LOW);
        INFO(name, "##     ##  ##     ##  ##     ##  ##     ##", LOW);
        INFO(name, "##     ##  ##     ##  ##         ##       ", LOW);
        INFO(name, "########   #########    ######     ###### ", LOW);
        INFO(name, "##         ##     ##         ##         ##", LOW);
        INFO(name, "##         ##     ##  ##     ##  ##     ##", LOW);
        INFO(name, "##         ##     ##    ######     ###### ", LOW);
        INFO(name, "                                          ", LOW);
        INFO(name, "Simfirtion completed without errors!", LOW);
      }
    }

    //+--------------------------------------------------------------------------
    //| FUNCTION: finish_phase
    //+--------------------------------------------------------------------------
    //! Virtual Function to finish simfirtion 
    //+--------------------------------------------------------------------------
    virtual void finish_phase(){
      INFO(name, "Start Finish Phase", MEDIUM);
       sc_stop(); // sc_stop triggers end of simfirtion
    }

};

