/*
 * monitor.hpp
 * Date Created: 08/09/24
*/

#ifndef MONITOR_HPP
#define MONITOR_HPP

#include "systemc.h"
#include "AvalonConf.hpp"

class Monitor : public sc_module {

public:
    sc_in<bool>                 clk;
    sc_in<bool>                 ready;
    sc_in<bool>                 valid;
    sc_in<sc_int<DATA_BITS>>    data;
    sc_in<sc_int<CHANNEL_BITS>> channel;
    sc_in<sc_int<ERROR_BITS>>   error;

    // Constructor
    Monitor(sc_module_name name);

    // Destructor
    ~Monitor();

private:
    std::string moduleName;
};

#endif // MONITOR_HPP