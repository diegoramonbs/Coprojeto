#include <ula_define.h>
#include <ula_sequence.h>
#include <ula_environment.h>

//+--------------------------------------------------------------------------
//| CLASS: ula_test_base
//+--------------------------------------------------------------------------
class ula_test_base {

  public :
    //+--------------------------------------------------------------------------
    //| Data Members
    //+--------------------------------------------------------------------------
    const char*  name;
    int          NI; // Number of interactions
    unsigned int seed; //Seed used in randomization and PRBS
    string testname;
    int sel;

    //+--------------------------------------------------------------------------
    //| Components Members
    //+--------------------------------------------------------------------------
    ula_environment* ula_env;
    
    //+--------------------------------------------------------------------------
    //| FUNCTION: constructor
    //+--------------------------------------------------------------------------
    ula_test_base(const char* _name,
                     ula_rst_interface* sc_rst_if,
                     ula_interface*     test_sc_if,
                     ula_interface*     rm_test_sc_if,
		                 test_config*       tst_cfg,
                     int sel_ = -1 ){
      INFO(_name, "Constructor", MEDIUM);
      ula_env = new ula_environment("ula_env", sc_rst_if, test_sc_if, rm_test_sc_if);
      name = _name;
      testname = tst_cfg->testname;
      NI   = tst_cfg->NI;
      seed = tst_cfg->seed;
      sel = sel_;
      srand(seed);
    }

    //+--------------------------------------------------------------------------
    //| FUNCTION: reset_phase
    //+--------------------------------------------------------------------------
    //! Virtual Function to implementation of reset phase
    //+--------------------------------------------------------------------------
    virtual void reset_phase(){
      INFO(name, "Start Reset Phase", MEDIUM);
      ula_env->ula_reset->async_reset();
      ula_env->ula_reset->wait_posedge(10); 
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
    //! Virtual Function to wait time to end of simulation
    //+--------------------------------------------------------------------------
    virtual void end_of_run_phase(){
      ula_env->ula_reset->wait_posedge(100); 
    }

    //+--------------------------------------------------------------------------
    //| FUNCTION: report_phase
    //+--------------------------------------------------------------------------
    //! Virtual Function to show the result of simulation
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
	msg << "Simulation completed with " << errors << " errors!";
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
        INFO(name, "Simulation completed without errors!", LOW);
      }
    }

    //+--------------------------------------------------------------------------
    //| FUNCTION: finish_phase
    //+--------------------------------------------------------------------------
    //! Virtual Function to finish simulation 
    //+--------------------------------------------------------------------------
    virtual void finish_phase(){
      INFO(name, "Start Finish Phase", MEDIUM);
       sc_stop(); // sc_stop triggers end of simulation
    }

};

