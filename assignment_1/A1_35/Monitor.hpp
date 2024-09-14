#pragma once

#include <systemc.h>

class Monitor :
    public sc_module
{
public:
    SC_CTOR(Monitor);

    sc_trace_file* trace_file;

    void initTracing();

    ~Monitor();
};

