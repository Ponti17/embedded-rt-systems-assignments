/*
 * AvalonMaster.cpp
 * Date Created: 29/08/24
*/

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
void AvalonMaster::transmit()
{
    std::cout << "Transmitting..." << std::endl;

    if (ready.read() == 1)
    {
        valid.write(1);
        data.write(0xFAFA);
        channel.write(1);
        error.write(0);
    }
}