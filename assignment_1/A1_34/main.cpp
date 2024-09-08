#include "systemc.h"
#include "AvalonMaster.hpp"

#define SIMULATION_TIME 200
#define SIMULATION_TIME_UNIT SC_MS

int sc_main(int sc_argc, char* sc_argv[])
{
    sc_clock clk("Clk", sc_time(20, SC_MS));
    sc_signal<bool>                 ready;
    sc_signal<bool>                 valid;
    sc_signal<sc_int<DATA_BITS>>    data;
    sc_signal<sc_int<CHANNEL_BITS>> channel;
    sc_signal<sc_int<ERROR_BITS>>   error;

    AvalonMaster avalonMaster("avalonMaster");

    avalonMaster.clk(clk);
    avalonMaster.ready(ready);
    avalonMaster.valid(valid);
    avalonMaster.data(data);
    avalonMaster.channel(channel);
    avalonMaster.error(error);

    // invoke the simulator
    sc_start(SIMULATION_TIME, SIMULATION_TIME_UNIT);
	std::cout << "Simulation finished at " << sc_time_stamp() << std::endl;
    return 0;
}