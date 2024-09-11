/*
 * AvalonMaster.cpp
 * Date Created: 29/08/24
*/

#include <iostream>
#include <string>
#include "AvalonMaster.hpp"

/* Constructor */
AvalonMaster::AvalonMaster(sc_module_name name) 
    : sc_module(name), moduleName(name)
{
    /* Register a thread process */
    SC_METHOD(transmit);
    sensitive << clk.pos();
}

/* Destructor */
AvalonMaster::~AvalonMaster()
{
    std::cout << std::flush;
}

/* Thread */
const uint8_t message_len = 14;
const char message[message_len] = "Hello, World!";
uint8_t idx = 0;
void AvalonMaster::transmit()
{
    std::cout << "Transmitting..." << std::endl;

    if (idx < message_len)
    {
        valid.write(1);
        data.write(message[idx]);
        channel.write(1);
        error.write(0);
        ++idx;
    }
    else
    {
        valid.write(0);
    }
}