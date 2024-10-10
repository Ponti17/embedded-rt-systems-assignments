/*
 * mac.hpp
 * Date Created: 04/09/24
*/

#ifndef MAC_HPP
#define MAC_HPP

#include "systemc.h"
#include <iostream>
#include <string>

class Mac : public sc_module {

public:
    // Constructor
    Mac(sc_module_name name);

    // Destructor
    ~Mac();

    sc_uint<32> accumulator = 0;
    sc_in<int> input_a;
    sc_in<int> input_b;

private:
    std::string moduleName;
    void multiplyAccumulate();  // Thread function declaration
};

#endif // MAC_HPP