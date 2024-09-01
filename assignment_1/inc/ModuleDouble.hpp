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
    /* Events */
    sc_event event_A, event_B, event_Aack, event_Back;

    /* Constructor */
    ModuleDouble(sc_module_name name);

    // Destructor
    ~ModuleDouble();

private:
    std::string moduleName;
    void thread_A();
    void thread_B();
    void method_A();
};

#endif // MODULE_DOUBLE_HPP