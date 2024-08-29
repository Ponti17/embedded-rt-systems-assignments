#include "systemc.h"
#include "ModuleDouble.hpp"

#define SIMULATION_TIME 200
#define SIMULATION_TIME_UNIT SC_MS

int sc_main(int sc_argc, char* sc_argv[])
{
	// Create instance of the SystemC module
    ModuleDouble ModuleDouble_i("ModuleDouble_i");

    // invoke the simulator
    sc_start(SIMULATION_TIME, SIMULATION_TIME_UNIT);
	std::cout << "Simulation finished at " << sc_time_stamp() << std::endl;
    return 0;
}