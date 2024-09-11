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
const uint8_t message_len = 13;
char message[] = "Hello, World!";
uint8_t idx = 0;
void AvalonMaster::transmit()
{
    std::cout << "Transmitting..." << std::endl;

    if (idx < message_len)
    {
        valid.write(1);

        uint16_t bin_data = message[idx];  // First character (low byte)

        if (idx + 1 < message_len)         // Ensure there's another char for the high byte
        {
            bin_data |= (message[idx + 1] << 8); // Second character (high byte)
        }

        data.write(bin_data);  // Transmit the combined data as uint16_t
        channel.write(1);
        error.write(0);
        idx += 2;  // Move to the next two characters
    }
    else
    {
        valid.write(0);
    }
}