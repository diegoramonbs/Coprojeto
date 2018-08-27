
//+--------------------------------------------------------------------------
//| CLASS: ula_test_random
//+--------------------------------------------------------------------------
class ula_test_random : public ula_test_base {
  public :
    //+--------------------------------------------------------------------------
    //| FUNCTION: constructor
    //+--------------------------------------------------------------------------
    ula_test_random(const char* _name,
                          ula_rst_interface* sc_rst_if, 
                          ula_interface*     test_sc_if,
			                    ula_interface*     rm_test_sc_if,
                          test_config*       tst_cfg,
                          int sel = -1 ) : ula_test_base(_name, sc_rst_if, test_sc_if, rm_test_sc_if, tst_cfg, sel){ 
  }

    //+--------------------------------------------------------------------------
    //| FUNCTION: configure_phase
    //+--------------------------------------------------------------------------
    //! Set the function of the checker for this test
    //---------------------------------------------------------------------------
    virtual void configure_phase(){
      INFO(name, "Configure Phase");
      ula_env->config_checker(1);
    }

    //+--------------------------------------------------------------------------
    //| FUNCTION: run_phase
    //+--------------------------------------------------------------------------
    //! Implement the test run
    //---------------------------------------------------------------------------
    void run_phase(){
      INFO(name, " Starting test...");
      
      INFO(name, " Set seed");
      ula_env->ula_drv->set_seed(seed);
      
      if( sel != -1)
      {
         for(int i = 0; i < NI; i++) 
         {
            INFO(name, " Generate random data");
            ula_env->ula_drv->randomize(sel);
         }
      } else {
        for(int i = 0; i < NI; i++) 
        {
            INFO(name, " Generate random data");
	        ula_env->ula_drv->randomize();
        }
      } 

      
      INFO(name, " Finished test!!!");
    }

    //+--------------------------------------------------------------------------
    //| FUNCTION: end_of_run_phase
    //+--------------------------------------------------------------------------
    //! Wait time to end of silmuation
    //+--------------------------------------------------------------------------
    virtual void end_of_run_phase(){
      ula_env->ula_reset->wait_posedge(1);  
    }
};
