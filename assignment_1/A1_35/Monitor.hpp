#pragma once

#include <systemc.h>

class Monitor :
    public sc_module
{
public:

	sc_in<bool> clk;
    sc_signal<sc_logic>* reset_signal;

    SC_CTOR(Monitor);

    sc_trace_file* trace_file;

    void initTracing();

    ~Monitor();
};

