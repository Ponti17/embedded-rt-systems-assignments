#pragma once

#include <systemc.h>

class Monitor :
    public sc_module
{
public:

	sc_in_clk clk;
    sc_in<sc_logic> reset_signal;
    sc_in<sc_logic> valid;

    SC_CTOR(Monitor);

    sc_trace_file* trace_file;

    void initTracing();

    ~Monitor();
};

