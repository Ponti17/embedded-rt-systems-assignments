#include <systemc.h>
#include <iostream>

#include "ModuleSingle.h"

#define SIMULATION_TIME 200
#define SIMULATION_TIME_UNIT SC_MS

int sc_main(int sc_argc, char* sc_argv[])
{
	ModuleSingle moduleSingle_i("Test_Module_single_1");

	sc_start(SIMULATION_TIME, SIMULATION_TIME_UNIT);

	std::cout << "Simulation finished at " << sc_time_stamp() << std::endl;

	return 0;
}