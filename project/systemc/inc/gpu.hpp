/*
 * gpu.hpp
 * Date Created: 09/11/24
*/

#ifndef GPU_HPP
#define GPU_HPP

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

#endif // GPU_HPP
