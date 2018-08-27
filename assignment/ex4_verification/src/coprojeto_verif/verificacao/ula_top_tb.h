SC_MODULE(ula_top_tb) {
    //+--------------------------------------------------------------------------
    //| Members
    //+--------------------------------------------------------------------------
    // Interface
    ula_rst_interface *rst_if;
    ula_interface     *ula_if;
    ula_interface     *rm_out_if;

    // DUT Module
    ula    DUT;
    rm_ula RM;

    // Test Module
    ula_test *test;
    
    #ifdef _TRACE_
      sc_trace_file *tf;
      string        trace_fname;
    #endif
    //+--------------------------------------------------------------------------
    //| FUNCTION: constructor
    //+--------------------------------------------------------------------------

     ula_top_tb(sc_module_name name, string _testname, string _trace_fname, test_config* tst_cfg)
   : DUT("DUT"),
     RM("RM"),
     sc_module(name)
   {
    // Interface
    rst_if     = new ula_rst_interface();   //reset
    ula_if     = new ula_interface();
    rm_out_if  = new ula_interface();
    
    //-----------------------------
    // DUT Module
    //-----------------------------    
    //Input signals
    DUT.clock   (rst_if->clk);          
    DUT.reset_n (rst_if->reset_n);

    DUT.in_data_en  (ula_if->in_data_en);
    DUT.in_data_a   (ula_if->in_data_a);
    DUT.in_data_b   (ula_if->in_data_b);
    DUT.in_sel      (ula_if->in_sel);

    //Output signals
    DUT.out_data    (ula_if->out_data);
    DUT.out_carryout(ula_if->out_carryout);
    DUT.out_data_rdy(ula_if->out_data_rdy);

    //-----------------------------
    // Reference Module
    //-----------------------------
    //Input signals
    RM.clock   (rst_if->clk);          
    RM.reset_n (rst_if->reset_n);

    RM.in_data_en  (ula_if->in_data_en);
    RM.in_data_a   (ula_if->in_data_a);
    RM.in_data_b   (ula_if->in_data_b);
    RM.in_sel      (ula_if->in_sel);

    //Output signals
    RM.out_data    (rm_out_if->out_data);
    RM.out_carryout(rm_out_if->out_carryout);
    RM.out_data_rdy(rm_out_if->out_data_rdy);

    //-----------------------------
    // Test Module
    //-----------------------------
    test = new ula_test(_testname.c_str(),
                            rst_if,
                            ula_if,
                            rm_out_if,
                            tst_cfg);
    test->clock(rst_if->clk);

    #ifdef _TRACE_
      tf = 0;
      trace_fname = _trace_fname;
    #endif

    }

    //+--------------------------------------------------------------------------
    //| FUNCTION: before_end_of_elaboration
    //+--------------------------------------------------------------------------
    //! Used to create the trace file
    //+--------------------------------------------------------------------------
    void before_end_of_elaboration(){
      #ifdef _TRACE_
        tf = sc_create_vcd_trace_file(trace_fname.c_str());
	tf->set_time_unit(0.5, SC_PS);
      #endif
    }

    //+--------------------------------------------------------------------------
    //| FUNCTION: end_of_elaboration
    //+--------------------------------------------------------------------------
    //! Used to connect the interface signals to trace file
    //+--------------------------------------------------------------------------
    void end_of_elaboration(){
      #ifdef _TRACE_
        sc_trace(tf, rst_if->clk, "clk");
        sc_trace(tf, rst_if->reset_n, "reset_n");

        sc_trace(tf, ula_if->in_data_en, "in_data_en");
        sc_trace(tf, ula_if->in_data_a,  "in_data_a");
        sc_trace(tf, ula_if->in_data_b,  "in_data_b");
        sc_trace(tf, ula_if->in_sel ,    "in_sel");
        
	sc_trace(tf, ula_if->out_data    , "out_data");
        sc_trace(tf, ula_if->out_data_rdy, "out_data_rdy");
        
	sc_trace(tf, rm_out_if->out_data    , "rm_out_data");
        sc_trace(tf, rm_out_if->out_data_rdy, "rm_out_data_rdy");
        
       #endif
    }

    //+--------------------------------------------------------------------------
    //| FUNCTION: end_of_simulation
    //+--------------------------------------------------------------------------
    //! Used to close the trace file
    //+--------------------------------------------------------------------------
    void end_of_simulation() {
      #ifdef _TRACE_
        sc_close_vcd_trace_file(tf);
      #endif
    }
}; 

