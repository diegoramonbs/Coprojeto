
//+--------------------------------------------------------------------------
//| CLASS: ula_test_sanity
//+--------------------------------------------------------------------------
class ula_test_sanity : public ula_test_base {
  public :
    //+--------------------------------------------------------------------------
    //| FUNCTION: constructor
    //+--------------------------------------------------------------------------
    ula_test_sanity(const char* _name,
                          ula_rst_interface* sc_rst_if, 
                          ula_interface*     test_sc_if,
			  ula_interface*     rm_test_sc_if,
                          test_config*       tst_cfg) : ula_test_base(_name, sc_rst_if, test_sc_if, rm_test_sc_if, tst_cfg){ 
  }

    //+--------------------------------------------------------------------------
    //| FUNCTION: configure_phase
    //+--------------------------------------------------------------------------
    //! Set the function of the checker for this test
    //---------------------------------------------------------------------------
    virtual void configure_phase(){
      INFO(name, "Configure Phase");
      ula_env->config_checker(0);
    }

    //+--------------------------------------------------------------------------
    //| FUNCTION: run_phase
    //+--------------------------------------------------------------------------
    //! Implement the test run
    //---------------------------------------------------------------------------
    void run_phase(){
      INFO(name, " Starting test...");
      ula_env->ula_drv->set_seed(seed);
      
      ula_env->ula_reset->wait_posedge(1);
      
      INFO(name, " Finished test!!!");
    }

    //+--------------------------------------------------------------------------
    //| FUNCTION: end_of_run_phase
    //+--------------------------------------------------------------------------
    //! Wait time to end of silmuation
    //+--------------------------------------------------------------------------
    virtual void end_of_run_phase(){
      ula_env->ula_reset->wait_posedge(100);  
    }
};
