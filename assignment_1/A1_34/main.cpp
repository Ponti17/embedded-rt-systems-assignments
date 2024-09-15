#include "systemc.h"
#include "AvalonMaster.hpp"
#include "top.hpp"

#define SIMULATION_TIME 100
#define SIMULATION_TIME_UNIT SC_US

int sc_main(int sc_argc, char* sc_argv[])
{
    Top top("top");

    // invoke the simulator
    sc_start(SIMULATION_TIME, SIMULATION_TIME_UNIT);

	std::cout << "Simulation finished at " << sc_time_stamp() << std::endl;

    return 0;
}