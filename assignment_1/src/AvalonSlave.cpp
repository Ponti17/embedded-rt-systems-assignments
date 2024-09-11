/*
 * AvalonSlave.cpp
 * Date Created: 29/08/24
*/

#include "AvalonSlave.hpp"

/* Constructor */
AvalonSlave::AvalonSlave(sc_module_name name) 
    : sc_module(name), moduleName(name)
{
    /* Register a thread process */
    SC_METHOD(receive);
    sensitive << clk.pos();
}

/* Destructor */
AvalonSlave::~AvalonSlave()
{
    std::cout << std::flush;
}

/* Thread */
uint16_t buf[120];
uint8_t buf_idx = 0;
void AvalonSlave::receive()
{
    ready.write(1);
    if (valid.read() == 1)
    {
        std::cout << "RECEIVING" << std::endl;
        buf[buf_idx] = data.read();
        ++buf_idx;
    }
    if (valid.read() == 0)
    {
        for (uint8_t i = 0; i < buf_idx; i++)
        {
            // Extract and print two chars from each uint16_t
            char high_byte = (buf[i] >> 8) & 0xFF; // Upper 8 bits
            char low_byte = buf[i] & 0xFF;         // Lower 8 bits

            std::cout << low_byte << high_byte;
        }
        std::cout << std::endl;
    }
}