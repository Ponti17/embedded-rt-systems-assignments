/*
 * AvalonSlave.hpp
 * Date Created: 04/09/24
*/

#ifndef AVALON_SLAVE_HPP
#define AVALON_SLAVE_HPP

#include "systemc.h"
#include <iostream>
#include <string>

class AvalonSlave : public sc_module {

public:
    // Constructor
    AvalonSlave(sc_module_name name);

    // Destructor
    ~AvalonSlave();

private:
    std::string moduleName;
    void mainThread();  // Thread function declaration
};

#endif // AVALON_SLAVE_HPP