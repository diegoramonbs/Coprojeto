SC_MODULE(fir_top_tb) {
    //+--------------------------------------------------------------------------
    //| Members
    //+--------------------------------------------------------------------------
    // Interface
    fir_rst_interface *rst_if;
    fir_interface     *fir_if;
    fir_interface     *rm_out_if;

    // DUT Module
    fir    DUT;
    rm_fir RM;

    // Test Module
    fir_test *test;
    
    #ifdef _TRACE_
      sc_trace_file *tf;
      string        trace_fname;
    #endif
    //+--------------------------------------------------------------------------
    //| FUNCTION: constructor
    //+--------------------------------------------------------------------------

     fir_top_tb(sc_module_name name, string _testname, string _trace_fname, test_config* tst_cfg)
   : DUT("DUT"),
     RM("RM"),
     sc_module(name)
   {
    // Interface
    rst_if     = new fir_rst_interface();   //reset
    fir_if     = new fir_interface();
    rm_out_if  = new fir_interface();
    
    //-----------------------------
    // DUT Module
    //-----------------------------    
    //Input signals
    DUT.clock   (rst_if->clk);          
    DUT.reset_n (rst_if->reset_n);

    DUT.in_data_en  (fir_if->in_data_en);
    DUT.sample   (fir_if->sample);

    //Output signals
    DUT.result    (fir_if->result);
    DUT.out_data_rdy(fir_if->out_data_rdy);

    //-----------------------------
    // Reference Module
    //-----------------------------
    //Input signals
    RM.clock   (rst_if->clk);          
    RM.reset_n (rst_if->reset_n);

    RM.in_data_en  (fir_if->in_data_en);
    RM.sample   (fir_if->sample);
    

    //Output signals
    RM.result   (rm_out_if->result);
    RM.out_data_rdy(rm_out_if->out_data_rdy);

    //-----------------------------
    // Test Module
    //-----------------------------
    test = new fir_test(_testname.c_str(),
                            rst_if,
                            fir_if,
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

        sc_trace(tf, fir_if->in_data_en, "in_data_en");
        sc_trace(tf, fir_if->sample,  "sample");
        
	    sc_trace(tf, fir_if->result    , "result");
        sc_trace(tf, fir_if->out_data_rdy, "out_data_rdy");
        
	sc_trace(tf, rm_out_if->result    , "result");
        sc_trace(tf, rm_out_if->out_data_rdy, "rm_out_data_rdy");
        
       #endif
    }

    //+--------------------------------------------------------------------------
    //| FUNCTION: end_of_simfirtion
    //+--------------------------------------------------------------------------
    //! Used to close the trace file
    //+--------------------------------------------------------------------------
    void end_of_simfirtion() {
      #ifdef _TRACE_
        sc_close_vcd_trace_file(tf);
      #endif
    }
}; 

