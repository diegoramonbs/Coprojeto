#include <ula_environment.h>

//+--------------------------------------------------------------------------
//| SC_MODULE: ula_test
//+--------------------------------------------------------------------------
SC_MODULE (ula_test) {
    //+--------------------------------------------------------------------------
    //| Input
    //+--------------------------------------------------------------------------
    sc_in<bool> clock;

    //+--------------------------------------------------------------------------
    //| Running test
    //+--------------------------------------------------------------------------
    ula_test_base* t;

    //+--------------------------------------------------------------------------
    //| Function Members
    //+--------------------------------------------------------------------------
    void select_phase();
  
    //+--------------------------------------------------------------------------
    //| FUNCTION: constructor
    //+--------------------------------------------------------------------------
    SC_HAS_PROCESS(ula_test);
     ula_test(sc_module_name name, 
                 ula_rst_interface* sc_rst_if, 
                 ula_interface*     test_sc_if,
                 ula_interface*     rm_test_sc_if,
                 test_config*       tst_cfg)
   : sc_module(sc_module_name("ula_test"))
   {
      if (string(name) == "ula_test_sanity") {
        t = new ula_test_sanity(name, sc_rst_if, test_sc_if, rm_test_sc_if, tst_cfg);
      }
      else if (string(name) == "ula_test_random") {
        t = new ula_test_random(name, sc_rst_if, test_sc_if, rm_test_sc_if, tst_cfg);
      }

      else if (string(name) == "ula_test_op0") {
        t = new ula_test_random(name, sc_rst_if, test_sc_if, rm_test_sc_if, tst_cfg, 0);
      }
      else if (string(name) == "ula_test_op1") {
        t = new ula_test_random(name, sc_rst_if, test_sc_if, rm_test_sc_if, tst_cfg, 1);
      }
      else if (string(name) == "ula_test_op2") {
        t = new ula_test_random(name, sc_rst_if, test_sc_if, rm_test_sc_if, tst_cfg, 2);
      }
      else if (string(name) == "ula_test_op3") {
        t = new ula_test_random(name, sc_rst_if, test_sc_if, rm_test_sc_if, tst_cfg, 3);
      }
      else if (string(name) == "ula_test_op4") {
        t = new ula_test_random(name, sc_rst_if, test_sc_if, rm_test_sc_if, tst_cfg, 4);
      }
      else if (string(name) == "ula_test_op5") {
        t = new ula_test_random(name, sc_rst_if, test_sc_if, rm_test_sc_if, tst_cfg, 5);
      }
      else if (string(name) == "ula_test_op6") {
        t = new ula_test_random(name, sc_rst_if, test_sc_if, rm_test_sc_if, tst_cfg, 6);
      }
      else if (string(name) == "ula_test_op7") {
        t = new ula_test_random(name, sc_rst_if, test_sc_if, rm_test_sc_if, tst_cfg, 7);
      }
      else  {
        SC_REPORT_FATAL(name, "Test not register");
      }

      SC_CTHREAD(select_phase,clock.pos());
    }
}; 

//+--------------------------------------------------------------------------
//| FUNCTION: select_phase
//+--------------------------------------------------------------------------
//! Function responsible to call the phases of the test
//+-------------------------------------------------------------------------
void ula_test::select_phase() {
   //Call Reset Phase
   t->reset_phase();

   //Call Configure Phase
   t->configure_phase();

   //Call Run Phase
   t->run_phase();

   //Call End of Run Phase
   t->end_of_run_phase();

   //Call Report Phase
   t->report_phase();

   //Call Finish Phase
   t->finish_phase();
}
