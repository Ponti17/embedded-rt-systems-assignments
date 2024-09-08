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
    sc_in<bool>               ready;
    sc_out<bool>              valid;
    sc_out<bool>              error;
    sc_out<bool>              channel;
    sc_out<sc_int<DATA_BITS>> data;

    // Constructor
    AvalonMaster(sc_module_name name);

    // Destructor
    ~AvalonMaster();

private:
    std::string moduleName;
    void mainThread();  // Thread function declaration
};

#endif // AVALON_MASTER_HPP