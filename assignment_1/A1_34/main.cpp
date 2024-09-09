#include "systemc.h"
#include "AvalonMaster.hpp"
#include "top.hpp"

#define SIMULATION_TIME 200
#define SIMULATION_TIME_UNIT SC_MS

int sc_main(int sc_argc, char* sc_argv[])
{
    Top top("top");

    // invoke the simulator
    sc_start(SIMULATION_TIME, SIMULATION_TIME_UNIT);
	std::cout << "Simulation finished at " << sc_time_stamp() << std::endl;
    return 0;
}