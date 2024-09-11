/*
 * top.cpp
 * Date Created: 08/09/24
*/

#include "top.hpp"

/* Constructor */
Top::Top(sc_module_name name) : sc_module(name), clk("clk", CLK_PERIOD, SC_US)
{
    pMaster     = new AvalonMaster("AvalonMaster");
    pSlave      = new AvalonSlave("AvalonSlave");
    pMonitor    = new Monitor("Monitor");

    pMaster->clk(clk);
    pMaster->ready(ready);
    pMaster->valid(valid);
    pMaster->data(data);
    pMaster->channel(channel);
    pMaster->error(error);

    pSlave->clk(clk);
    pSlave->ready(ready);
    pSlave->valid(valid);
    pSlave->data(data);
    pSlave->channel(channel);
    pSlave->error(error);

    pMonitor->clk(clk);
    pMonitor->ready(ready);
    pMonitor->valid(valid);
    pMonitor->data(data);
    pMonitor->channel(channel);
    pMonitor->error(error);
}

/* Destructor */
Top::~Top()
{
    std::cout << std::flush;
}