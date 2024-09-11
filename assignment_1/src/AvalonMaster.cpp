/*
 * AvalonMaster.cpp
 * Date Created: 04/09/24
*/

#include <iostream>
#include <string>
#include "AvalonMaster.hpp"

/* Constructor */
AvalonMaster::AvalonMaster(sc_module_name name) 
    : sc_module(name), moduleName(name)
{
    binaryPacket = 0;
    message = "Hello, World!\nThis is transmitted over the Avalon Streaming Interface!";

    SC_METHOD(transmit);
    sensitive << clk.pos();
}

/* Destructor */
AvalonMaster::~AvalonMaster()
{
    std::cout << std::flush;
}

static uint32_t idx = 0;
static bool readyDelay = false;
void AvalonMaster::transmit()
{
    if (ready.read() == 1 && !readyDelay)
    {
        readyDelay = true;
    }
    else if (readyDelay && idx < message.length())
    {
        std::cout << "Transmitting..." << std::endl;
        valid.write(1);
        binaryPacket = 0;
        for (int i = 0; i < DATA_BITS / 8; ++i)
        {
            binaryPacket |= (message[idx + i] << 8 * i);
        }
        data.write(binaryPacket);
        idx += DATA_BITS / 8;
    }
    else
    {
        valid.write(0);
        readyDelay = false;
    }
}