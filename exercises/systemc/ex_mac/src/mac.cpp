/*
 * mac.cpp
 * Date Created: 04/09/24
*/

#include "mac.hpp"

/* Constructor */
Mac::Mac(sc_module_name name) 
    : sc_module(name), moduleName(name)
{
    /* Register one method */
    SC_METHOD(multiplyAccumulate);
    sensitive << input_a << input_b;
    dont_initialize();
}

/* Destructor */
Mac::~Mac()
{
    std::cout << std::flush;
}

void Mac::multiplyAccumulate()
{
    accumulator += input_a.read() * input_b.read();
    std::cout << " Time: " << sc_time_stamp() << "  -  Accumulator: " << accumulator << std::endl;
}