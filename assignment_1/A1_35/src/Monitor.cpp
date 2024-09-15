#include "Monitor.hpp"

Monitor::Monitor(sc_module_name name,
    sc_signal<sc_logic>& reset_signal,
    sc_signal<sc_logic>& ready_signal,
    sc_signal<sc_logic>& valid_signal,
    sc_signal<CHANNEL_BITS>& channel_signal,
    sc_signal<ERROR_BITS>& error_signal,
    sc_signal<DATA_BITS>& data_signal)
    : sc_module(name),
    clock("clock"),
    reset_signal(reset_signal),
    ready_signal(ready_signal),
    valid_signal(valid_signal),
    channel_signal(channel_signal),
    error_signal(error_signal),
    data_signal(data_signal)
{
    
    trace_file = sc_create_vcd_trace_file("waveform");

    sc_trace(trace_file, clock, "clock");
    sc_trace(trace_file, reset_signal, "reset");
    sc_trace(trace_file, ready_signal, "ready");
    sc_trace(trace_file, valid_signal, "valid");
    sc_trace(trace_file, channel_signal, "channel");
    sc_trace(trace_file, error_signal, "error");
    sc_trace(trace_file, data_signal, "data");

    // SC_METHOD(monitor_signals);
    sensitive << clock.pos();
}

void Monitor::monitor_signals() {
    std::cout << "Time: " << sc_time_stamp()
        << " | reset: " << reset_signal.read().to_char()
        << " | ready: " << ready_signal.read().to_char()
        << " | valid: " << valid_signal.read().to_char()
        << " | channel: " << channel_signal.read()
        << " | error: " << error_signal.read()
        << " | data: " << data_signal.read()
        << std::endl;
}

Monitor::~Monitor() {
    sc_close_vcd_trace_file(trace_file);
}
