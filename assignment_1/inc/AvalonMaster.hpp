/*
 * AvalonMaster.hpp
 * Date Created: 04/09/24
*/

#ifndef AVALON_MASTER_HPP
#define AVALON_MASTER_HPP

#include "systemc.h"
#include <iostream>
#include <string>

class AvalonMaster : public sc_module {

public:
    // Constructor
    AvalonMaster(sc_module_name name);

    // Destructor
    ~AvalonMaster();

private:
    std::string moduleName;
    void mainThread();  // Thread function declaration
};

#endif // AVALON_MASTER_HPP