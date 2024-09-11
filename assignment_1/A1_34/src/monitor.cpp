/*
 * monitor.cpp
 * Date Created: 11/09/24
*/

#include <iostream>
#include <string>
#include "monitor.hpp"

/* Constructor */
Monitor::Monitor(sc_module_name name) 
    : sc_module(name), moduleName(name)
{
    tracefile = sc_create_vcd_trace_file("tracefile");
    tracefile->set_time_unit(1, SC_NS);
    sc_trace(tracefile, clk,    "clk");
    sc_trace(tracefile, ready,  "ready");
    sc_trace(tracefile, valid,  "valid");
    sc_trace(tracefile, data,   "data");
    sc_trace(tracefile, channel,"channel");
    sc_trace(tracefile, error,  "error");
}

/* Destructor */
Monitor::~Monitor()
{
    sc_close_vcd_trace_file(tracefile);
    std::cout << "Saved vcd..." << std::endl;
}