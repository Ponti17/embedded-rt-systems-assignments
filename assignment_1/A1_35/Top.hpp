#pragma once
//Library imports
#include <systemc.h>

// Class imports
#include "Slave.hpp"
#include "Master.hpp"
#include "InAdapter.hpp"
#include "Monitor.hpp"

class Top :
    public sc_module
{

public:
    sc_clock clock;
	sc_signal<sc_logic > reset;

    Master* master;
	InAdapter<sc_uint<8>> * adapter;
	Slave* slave;
	Monitor* monitor;

	SC_CTOR(Top);
};

