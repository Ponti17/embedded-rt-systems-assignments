/*
 * AvalonMaster.cpp
 * Date Created: 29/08/24
*/

#include <iostream>
#include <string>
#include "AvalonMaster.hpp"

/* Constructor */
sc_trace_file *file_handler = sc_create_vcd_trace_file("avalonTrace");
AvalonMaster::AvalonMaster(sc_module_name name) 
    : sc_module(name), moduleName(name)
{
    sc_trace(file_handler, clk, "clk");
    sc_trace(file_handler, ready, "ready");
    sc_trace(file_handler, valid, "valid");
    sc_trace(file_handler, data, "data");
    sc_trace(file_handler, channel, "channel");
    sc_trace(file_handler, error, "error");
}

/* Destructor */
AvalonMaster::~AvalonMaster()
{
    sc_close_vcd_trace_file(file_handler);
}