#pragma once

#include <systemc.h>
#include "defs.hpp"

class Monitor : public sc_module {
public:

    sc_trace_file* trace_file;

    sc_in<bool> clock;

    sc_signal<sc_logic>& reset_signal;
    sc_signal<sc_logic>& ready_signal;
    sc_signal<sc_logic>& valid_signal;
    sc_signal<CHANNEL_BITS>& channel_signal;
    sc_signal<ERROR_BITS>& error_signal;
    sc_signal<DATA_BITS>& data_signal;


    Monitor(sc_module_name name,
        sc_signal<sc_logic>& reset_signal,
        sc_signal<sc_logic>& ready_signal,
        sc_signal<sc_logic>& valid_signal,
        sc_signal<CHANNEL_BITS>& channel_signal,
        sc_signal<ERROR_BITS>& error_signal,
        sc_signal<DATA_BITS>& data_signal);

    ~Monitor();

private:
    void monitor_signals();
};
