/*
 * monitor.hpp
 * Date Created: 08/09/24
*/

#ifndef MONITOR_HPP
#define MONITOR_HPP

#include "systemc.h"

sc_trace_file *file_handler = sc_create_vcd_trace_file("trace");
sc_trace(file_handler, siga, "SignalA");
sc_trace(file_handler, sigb, "SignalB");
sc_trace(file_handler, testclk, "CLK");
sc_close_vcd_trace_file(file_handler);

#endif // MONITOR_HPP