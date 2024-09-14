#include "Top.hpp"


Top::Top(sc_module_name name) :
	sc_module(name),
	clock("clock", CLOCK_PERIOD, CLOCK_PERIOD_UNIT)
{

	sc_fifo<sc_uint<10>> fifo(8);

	master = new Master("master");
	adapter = new InAdapter<sc_uint<8>>("adapter");
	slave = new Slave("slave");
	monitor = new Monitor("monitor");

	adapter->clock(clock);
	adapter->reset(reset);
	slave->clock(clock);
	slave->reset(reset);

	//interconnects
	adapter->ready(slave->ready);
	slave->valid(adapter->valid);
	slave->data(adapter->data);
	slave->error(adapter->error);
	slave->channel(adapter->channel);

	reset.write(SC_LOGIC_1);

	sc_spawn([&]()
		{
			wait(100, SC_NS);
			reset.write(SC_LOGIC_0);
		});

}