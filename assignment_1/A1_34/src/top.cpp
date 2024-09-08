/*
 * top.cpp
 * Date Created: 08/09/24
*/

#include "top.hpp"

/* Constructor */
Top::Top(sc_module_name name) : sc_module(name)
{
    clock("Clk", sc_time(CLK_PERIOD, SC_US));
}

/* Destructor */
Top::~Top()
{
    std::cout << std::flush;
}