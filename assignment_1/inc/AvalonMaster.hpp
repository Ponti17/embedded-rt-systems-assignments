/*
 * AvalonMaster.hpp
 * Date Created: 04/09/24
*/

#ifndef AVALON_MASTER_HPP
#define AVALON_MASTER_HPP

#include "systemc.h"
#include <iostream>
#include <string>
#include "AvalonConf.hpp"

class AvalonMaster : public sc_module {

public:
    sc_in<bool>                     clk;
    sc_in<bool>                     ready;
    sc_out<bool>                    valid;
    sc_out<sc_int<DATA_BITS>>       data;
    sc_out<sc_int<CHANNEL_BITS>>    channel;
    sc_out<sc_int<ERROR_BITS>>      error;

    // Constructor
    AvalonMaster(sc_module_name name);

    // Destructor
    ~AvalonMaster();

private:
    std::string moduleName;
    void transmit();
};

#endif // AVALON_MASTER_HPP