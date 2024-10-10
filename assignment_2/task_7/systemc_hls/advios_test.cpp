#include <systemc.h>

#ifdef __RTL_SIMULATION__
	#include "advios_rtl_wrapper.h"
	#define advios advios_rtl_wrapper
#else
	#include "advios.h"
#endif

#include "advios_driver.h"

int sc_main(int argc, char * argv[]){
	sc_report_handler::set_actions("/IEEE_Std_1666/deprecated", SC_DO_NOTHING);
	sc_report_handler::set_actions( SC_ID_LOGIC_X_TO_BOOL_, SC_LOG);
	sc_report_handler::set_actions( SC_ID_VECTOR_CONTAINS_LOGIC_VALUE_, SC_LOG);
	sc_report_handler::set_actions( SC_ID_OBJECT_EXISTS_, SC_LOG);

	sc_trace_file *tracefile;

	sc_signal<bool> s_reset;
	sc_signal<sc_uint<4> > s_ctrl;
	sc_signal<sc_uint<4> > s_switch;
	sc_signal<sc_uint<4> > s_leds;
	sc_clock s_clock("s_clk", 10, SC_NS);

	advios u_advios("u_advios");
	advios_driver u_advios_driver("u_advios_driver");

	tracefile = sc_create_vcd_trace_file("wave");
	if (!tracefile) cout << "Could not create trace file." << endl;

	tracefile->set_time_unit(1, SC_NS);

	sc_trace(tracefile, s_clock, "clock");
	sc_trace(tracefile, s_reset, "reset");
	sc_trace(tracefile, s_ctrl, "ctrl");
	sc_trace(tracefile, s_switch, "switches");
	sc_trace(tracefile, s_leds, "leds");

	u_advios.clk(s_clock);
	u_advios.reset(s_reset);
	u_advios.ctrl(s_ctrl);
	u_advios.outLeds(s_leds);
	u_advios.inSwitch(s_switch);

	u_advios_driver.clk(s_clock);
	u_advios_driver.ctrl(s_ctrl);
	u_advios_driver.inLeds(s_leds);
	u_advios_driver.reset(s_reset);
	u_advios_driver.outSwitch(s_switch);

	sc_start(10000, SC_NS);

	sc_close_vcd_trace_file(tracefile);
	return 0;
}
