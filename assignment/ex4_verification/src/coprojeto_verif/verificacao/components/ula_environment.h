#ifndef _ENV_H_
#define _ENV_H_

#include <systemc.h>
#include <ula_pkg.h>
#include <ula_checker.h>
#include <ula_rst_interface.h>
#include <ula_rst.h>

SC_MODULE(ula_environment)
{
  public:
 
    //+--------------------------------------------------------------------------
    //| Components Members
    //+--------------------------------------------------------------------------
    ula_driver*   ula_drv;
    ula_monitor*  ula_dut_mon;
    ula_monitor*  ula_rm_mon;
    ula_checker*  ula_chk;

    ula_rst*      ula_reset;

    //+--------------------------------------------------------------------------
    //| FUNCTION: config_checker
    //+--------------------------------------------------------------------------
    //! Select the type of check for:
    //!   1 - Select compare_in_out
    //+--------------------------------------------------------------------------
    void config_checker(int config_checker){
       ula_chk->select_checker = config_checker;
    }
    
    //+--------------------------------------------------------------------------
    //| FUNCTION: constructor
    //+--------------------------------------------------------------------------
    SC_HAS_PROCESS(ula_environment);
       ula_environment(sc_module_name name, 
                          ula_rst_interface* sc_rst_if, 
                          ula_interface*     ula_vif, 
                          ula_interface*     ula_rm_vif): sc_module(name)
    {
      INFO(this->name(), "constructor");

      ula_reset = new ula_rst("ula_reset", sc_rst_if);
      ula_reset->clock(sc_rst_if->clk);
      ula_reset->clock2(sc_rst_if->clk2);
       
      ula_drv = new ula_driver("ula_drv",ula_vif);
      ula_drv->clk(sc_rst_if->clk);
      ula_drv->async_reset(sc_rst_if->reset_n);

      ula_dut_mon = new ula_monitor("ula_dut_mon",ula_vif);  
      ula_dut_mon->clk(sc_rst_if->clk);
      ula_dut_mon->async_reset(sc_rst_if->reset_n);

      ula_rm_mon = new ula_monitor("ula_rm_mon",ula_rm_vif);  
      ula_rm_mon->clk(sc_rst_if->clk);
      ula_rm_mon->async_reset(sc_rst_if->reset_n);

      ula_chk = new ula_checker("ula_chk");
      ula_chk->clk(sc_rst_if->clk);
      ula_chk->clk2(sc_rst_if->clk2);
      ula_chk->async_reset(sc_rst_if->reset_n);

      ula_drv->drv_port.bind(ula_chk->chk_drv_port);      
      ula_dut_mon->mon_port.bind(ula_chk->chk_port);
      ula_rm_mon->mon_port.bind(ula_chk->chk_rm_port);
    }

};

#endif /* VIP_SC_ENV_H_ */
