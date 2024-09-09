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
    /* Read the message to be sent through the Avalon interface */
    ifstream ifs("C:/home/university/7-semester/embedded-rt-systems-assignments/assignment_1/A1_34/message.txt");

    if (!ifs.is_open())
    {
        std::cerr << "Failed to read" << std::endl;
    }

    std::ostringstream oss;
    oss << ifs.rdbuf();
    std::string message = oss.str();

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