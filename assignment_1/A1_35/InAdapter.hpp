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

	InAdapter(sc_module_name name);

	void write(const T& data) override;

private:
	bool nb_write(const T& data) override;
	int num_free() const override;
	const sc_event& data_read_event() const override;

};

