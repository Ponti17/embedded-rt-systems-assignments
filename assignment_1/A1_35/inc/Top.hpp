#pragma once
//Library imports
#include <systemc.h>

// Class imports
#include "Slave.hpp"
#include "Master.hpp"
#include "InAdapter.hpp"
#include "Monitor.hpp"
#include "defs.hpp"

class Top :
    public sc_module
{

public:
    sc_clock clock;
	sc_signal<sc_logic > reset;

    sc_signal<sc_logic> ready_signal;
    sc_signal<sc_logic> valid_signal;
    sc_signal<CHANNEL_BITS> channel_signal;
    sc_signal<ERROR_BITS> error_signal;
    sc_signal<DATA_BITS> data_signal;

    Master* master;
	InAdapter<sc_uint<8>> * adapter;
	Slave* slave;
	Monitor* monitor;

	SC_CTOR(Top);
};

