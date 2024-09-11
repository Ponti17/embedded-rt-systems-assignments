/*
 * AvalonSlave.hpp
 * Date Created: 04/09/24
*/

#ifndef AVALON_SLAVE_HPP
#define AVALON_SLAVE_HPP

#include "systemc.h"
#include <iostream>
#include <string>
#include "AvalonConf.hpp"

class AvalonSlave : public sc_module {

public:
    sc_in<bool>                 clk;
    sc_out<bool>                ready;
    sc_in<bool>                 valid;
    sc_in<sc_int<DATA_BITS>>    data;
    sc_in<sc_int<CHANNEL_BITS>> channel;
    sc_in<sc_int<ERROR_BITS>>   error;

    // Constructor
    AvalonSlave(sc_module_name name);

    // Destructor
    ~AvalonSlave();

private:
    std::string moduleName;
    void receive();
};

#endif // AVALON_SLAVE_HPP