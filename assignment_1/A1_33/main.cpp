#include "systemc.h"
#include "TCP_Producer.hpp"

#define SIMULATION_TIME 100
#define SIMULATION_TIME_UNIT SC_MS

int sc_main(int sc_argc, char* sc_argv[])
{
    // Create instance of the SystemC module
    TCP_Producer TCP_Producer_i("TCP_Producer_i");

    // invoke the simulator
    sc_start(SIMULATION_TIME, SIMULATION_TIME_UNIT);
    std::cout << "Simulation finished at " << sc_time_stamp() << std::endl;
    return 0;
}