#pragma once
#include <systemc.h>
#include "defs.hpp"

template <class T>
class InAdapter : public sc_module, public sc_fifo_out_if<T> {

public:

	sc_in_clk clock;
	sc_in<sc_logic> ready, reset;

	sc_out <sc_logic> valid;
	sc_out<CHANNEL_BITS> channel;
	sc_out<ERROR_BITS> error;
	sc_out<DATA_BITS> data;

	InAdapter(sc_module_name name) : sc_module(name) {};

	void write(const T& value)
	{

		if (reset.read() == SC_LOGIC_0) {

			while (ready.read() == SC_LOGIC_0)
			{

				wait(clock.posedge_event());

			}

			data.write(value);
			channel.write(0);
			error.write(0);
			valid.write(SC_LOGIC_1);

			wait(clock.posedge_event());
			valid.write(SC_LOGIC_0);

		}
		else {

			wait(clock.posedge_event());

		}

	}

private:
	
	bool nb_write(const T& value)
	{
		return false;
	}

	int num_free() const
	{
		return 0;
	}

	const sc_event& data_read_event() const
	{
		return *new sc_event();
	}
};

