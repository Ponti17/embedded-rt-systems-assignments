#include "Top.hpp"

Top::Top(sc_module_name name)
    : sc_module(name),
    clock("clock", CLOCK_PERIOD, CLOCK_PERIOD_UNIT),
    reset("reset"),
    ready_signal("ready_signal"),
    valid_signal("valid_signal"),
    channel_signal("channel_signal"),
    error_signal("error_signal"),
    data_signal("data_signal")
{

	sc_fifo<sc_uint<8>> fifo;

	master = new Master("master");
	adapter = new InAdapter<sc_uint<8>>("adapter");
	slave = new Slave("slave");
    monitor = new Monitor("monitor",
        reset,
        ready_signal,
        valid_signal,
        channel_signal,
        error_signal,
        data_signal);

    adapter->clock(clock);
    adapter->reset(reset);
    slave->clock(clock);
    slave->reset(reset);

    master->out_fifo(*adapter);

    adapter->ready(ready_signal);
    slave->ready(ready_signal);

    adapter->valid(valid_signal);
    slave->valid(valid_signal);

    adapter->data(data_signal);
    slave->data(data_signal);

    adapter->error(error_signal);
    slave->error(error_signal);

    adapter->channel(channel_signal);
    slave->channel(channel_signal);

    reset.write(SC_LOGIC_1);

	sc_spawn([&]()
		{
			wait(10, SC_NS);
			reset.write(SC_LOGIC_0);
		});

	monitor->clock(clock);

}