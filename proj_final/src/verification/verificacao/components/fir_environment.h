#ifndef _ENV_H_
#define _ENV_H_

#include <systemc.h>
#include <fir_pkg.h>
#include <fir_checker.h>
#include <fir_rst_interface.h>
#include <fir_rst.h>

SC_MODULE(fir_environment)
{
  public:
 
    //+--------------------------------------------------------------------------
    //| Components Members
    //+--------------------------------------------------------------------------
    fir_driver*   fir_drv;
    fir_monitor*  fir_dut_mon;
    fir_monitor*  fir_rm_mon;
    fir_checker*  fir_chk;

    fir_rst*      fir_reset;

    //+--------------------------------------------------------------------------
    //| FUNCTION: config_checker
    //+--------------------------------------------------------------------------
    //! Select the type of check for:
    //!   1 - Select compare_in_out
    //+--------------------------------------------------------------------------
    void config_checker(int config_checker){
       fir_chk->select_checker = config_checker;
    }
    
    //+--------------------------------------------------------------------------
    //| FUNCTION: constructor
    //+--------------------------------------------------------------------------
    SC_HAS_PROCESS(fir_environment);
       fir_environment(sc_module_name name, 
                          fir_rst_interface* sc_rst_if, 
                          fir_interface*     fir_vif, 
                          fir_interface*     fir_rm_vif): sc_module(name)
    {
      INFO(this->name(), "constructor");

      fir_reset = new fir_rst("fir_reset", sc_rst_if);
      fir_reset->clock(sc_rst_if->clk);
      fir_reset->clock2(sc_rst_if->clk2);
       
      fir_drv = new fir_driver("fir_drv",fir_vif);
      fir_drv->clk(sc_rst_if->clk);
      fir_drv->async_reset(sc_rst_if->reset_n);

      fir_dut_mon = new fir_monitor("fir_dut_mon",fir_vif);  
      fir_dut_mon->clk(sc_rst_if->clk);
      fir_dut_mon->async_reset(sc_rst_if->reset_n);

      fir_rm_mon = new fir_monitor("fir_rm_mon",fir_rm_vif);  
      fir_rm_mon->clk(sc_rst_if->clk);
      fir_rm_mon->async_reset(sc_rst_if->reset_n);

      fir_chk = new fir_checker("fir_chk");
      fir_chk->clk(sc_rst_if->clk);
      fir_chk->clk2(sc_rst_if->clk2);
      fir_chk->async_reset(sc_rst_if->reset_n);

      fir_drv->drv_port.bind(fir_chk->chk_drv_port);      
      fir_dut_mon->mon_port.bind(fir_chk->chk_port);
      fir_rm_mon->mon_port.bind(fir_chk->chk_rm_port);
    }

};

#endif /* VIP_SC_ENV_H_ */
