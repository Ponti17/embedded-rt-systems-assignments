#pragma once

#include <systemc.h>
#include "defs.hpp"


class Slave : public sc_module {

public:

	sc_in_clk				clock;
	sc_in <sc_logic>		valid, reset;
	sc_in <DATA_BITS>		data;
	sc_in <ERROR_BITS>		error;
	sc_in <CHANNEL_BITS>	channel;

	sc_out <sc_logic>		ready;

	Slave(sc_module_name name);

private:

	void receive();

};

