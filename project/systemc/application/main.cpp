#include "systemc.h"
#include "gpu.hpp"

#define SIMULATION_TIME 200
#define SIMULATION_TIME_UNIT SC_MS

int sc_main(int sc_argc, char* sc_argv[])
{
	// Create instance of the SystemC module
	ModuleSingle ModuleSingle_i("ModuleSingle_i");

	// Invoke the simulator
	sc_start(SIMULATION_TIME, SIMULATION_TIME_UNIT);
	std::cout << "Simulation finished at " << sc_time_stamp() << std::endl;
	return 0;
}