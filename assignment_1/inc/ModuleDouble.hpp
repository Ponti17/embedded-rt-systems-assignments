/*
 * ModuleDouble.hpp
 * Date Created: 29/08/24
*/

#ifndef MODULE_DOUBLE_HPP
#define MODULE_DOUBLE_HPP

#include "systemc.h"
#include <iostream>
#include <string>

class ModuleDouble : public sc_module {

public:
    // Constructor
    ModuleDouble(sc_module_name name);

    // Destructor
    ~ModuleDouble();

private:
    std::string moduleName;
    void moduleDoubleThread();  // Thread function declaration
};

#endif // MODULE_DOUBLE_HPP