/*
 * ModuleSingle.hpp
 * Date Created: 29/08/24
*/

#ifndef MODULE_SINGLE_HPP
#define MODULE_SINGLE_HPP

#include "systemc.h"
#include <iostream>
#include <string>

class ModuleSingle : public sc_module {

public:
    /* Constructor */
    ModuleSingle(sc_module_name name);

    /* Destructor */
    ~ModuleSingle();

private:
    std::string moduleName;
    sc_uint<4> counter;
    sc_event event;

    /* Main thread entry */
    void moduleSingleThread();

    /* Increment */
    void incrementCounter();

    // Trigger function
    void trigger();
};

#endif // MODULE_SINGLE_HPP
