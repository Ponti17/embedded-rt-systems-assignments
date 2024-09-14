#include "Monitor.hpp"

Monitor::Monitor(sc_module_name name) : sc_module(name)
{
	SC_THREAD(initTracing);
}

void Monitor::initTracing()
{
	
	trace_file = sc_create_vcd_trace_file("waveform");

}
Monitor::~Monitor()
{
	sc_close_vcd_trace_file(trace_file);
}