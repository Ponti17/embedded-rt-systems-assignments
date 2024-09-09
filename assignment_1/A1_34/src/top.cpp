/*
 * top.cpp
 * Date Created: 08/09/24
*/

#include "top.hpp"

/* Constructor */
Top::Top(sc_module_name name) : sc_module(name), clk("clk", CLK_PERIOD, SC_US)
{
    pMaster = new AvalonMaster("AvalonMaster");

    pMaster->clk(clk);
    pMaster->ready(ready);
    pMaster->valid(valid);
    pMaster->data(data);
    pMaster->channel(channel);
    pMaster->error(error);
}

/* Destructor */
Top::~Top()
{
    std::cout << std::flush;
}