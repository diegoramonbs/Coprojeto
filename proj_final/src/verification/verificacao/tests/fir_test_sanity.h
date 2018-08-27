
//+--------------------------------------------------------------------------
//| CLASS: fir_test_sanity
//+--------------------------------------------------------------------------
class fir_test_sanity : public fir_test_base {
  public :
    //+--------------------------------------------------------------------------
    //| FUNCTION: constructor
    //+--------------------------------------------------------------------------
    fir_test_sanity(const char* _name,
                          fir_rst_interface* sc_rst_if, 
                          fir_interface*     test_sc_if,
			  fir_interface*     rm_test_sc_if,
                          test_config*       tst_cfg) : fir_test_base(_name, sc_rst_if, test_sc_if, rm_test_sc_if, tst_cfg){ 
  }

    //+--------------------------------------------------------------------------
    //| FUNCTION: configure_phase
    //+--------------------------------------------------------------------------
    //! Set the function of the checker for this test
    //---------------------------------------------------------------------------
    virtual void configure_phase(){
      INFO(name, "Configure Phase");
      fir_env->config_checker(0);
    }

    //+--------------------------------------------------------------------------
    //| FUNCTION: run_phase
    //+--------------------------------------------------------------------------
    //! Implement the test run
    //---------------------------------------------------------------------------
    void run_phase(){
      INFO(name, " Starting test...");
      fir_env->fir_drv->set_seed(seed);
      
      fir_env->fir_reset->wait_posedge(1);
      
      INFO(name, " Finished test!!!");
    }

    //+--------------------------------------------------------------------------
    //| FUNCTION: end_of_run_phase
    //+--------------------------------------------------------------------------
    //! Wait time to end of silmuation
    //+--------------------------------------------------------------------------
    virtual void end_of_run_phase(){
      fir_env->fir_reset->wait_posedge(100);  
    }
};
