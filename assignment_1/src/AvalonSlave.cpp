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
char buf[120];
uint8_t buf_idx = 0;
void AvalonSlave::receive()
{
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
            std::cout << buf[i];
        }
        std::cout << std::endl;
    }
}