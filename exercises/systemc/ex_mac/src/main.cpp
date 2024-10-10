#include "systemc.h"
#include "stimulus.hpp"
#include "mac.hpp"

constexpr int SIM_TIME = 1;
constexpr enum sc_time_unit SIM_TIME_UNIT = SC_MS;

int sc_main(int sc_argc, char* sc_argv[])
{
	sc_trace_file *file_handler = sc_create_vcd_trace_file("trace");

	sc_signal<int> siga, sigb, sigc;
	sc_clock testclk("clock", sc_time(20, SC_NS));

	// Invoke the simulator
	Stimulus stimmy("TEST");
	Mac myMac("MACDONALDS");
	stimmy.a(siga);
	stimmy.b(sigb);
	stimmy.clk(testclk);
	myMac.input_a(siga);
	myMac.input_b(sigb);
	
	sc_trace(file_handler, siga, "SignalA");
	sc_trace(file_handler, sigb, "SignalB");
	sc_trace(file_handler, testclk, "CLK");

	sc_start(SIM_TIME, SIM_TIME_UNIT);

	std::cout << "Simulation finished at " << sc_time_stamp() << std::endl;
	sc_close_vcd_trace_file(file_handler);
	return 0;
}