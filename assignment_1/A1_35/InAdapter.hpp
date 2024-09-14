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
			std::cout << "InAdapter: Waiting for ready signal at " << sc_time_stamp() << std::endl;
			std::cout << "inAdapter value read: " << value << std::endl;
			while (ready.read() == SC_LOGIC_0)
			{

				wait(clock.posedge_event());

			}
			std::cout << "InAdapter: Writing " << value << " at "<< sc_time_stamp() << std::endl;
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

		SC_REPORT_FATAL("/InAdapter", "Called nb_write()");
		return false;

	}

	int num_free() const
	{

		SC_REPORT_FATAL("/InAdapter", "Called num_free()");
		return -1;

	}

	const sc_event& data_read_event() const
	{

		SC_REPORT_FATAL("/InAdapter", "Called data_read_event()");
		static sc_event dummy_event;
		return dummy_event;

	}
};

