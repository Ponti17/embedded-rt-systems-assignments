/*
 * AvalonSlave.hpp
 * Date Created: 04/09/24
*/

#ifndef AVALON_SLAVE_HPP
#define AVALON_SLAVE_HPP

#include "systemc.h"
#include <iostream>
#include <string>

#define DATA_BITS 16

class AvalonSlave : public sc_module {

public:
    sc_out<bool>             ready;
    sc_in<bool>              valid;
    sc_in<bool>              error;
    sc_in<bool>              channel;
    sc_in<sc_int<DATA_BITS>> data;

    // Constructor
    AvalonSlave(sc_module_name name);

    // Destructor
    ~AvalonSlave();

private:
    std::string moduleName;
    void mainThread();  // Thread function declaration
};

#endif // AVALON_SLAVE_HPP