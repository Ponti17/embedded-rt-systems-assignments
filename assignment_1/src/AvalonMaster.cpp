/*
 * AvalonMaster.cpp
 * Date Created: 04/09/24
*/

#include <iostream>
#include <string>
#include "AvalonMaster.hpp"

/* Constructor */
AvalonMaster::AvalonMaster(sc_module_name name) : sc_module(name), moduleName(name) {
    message = "Hello, World!\nThis is transmitted over the Avalon Streaming Interface!";
    binaryPacket = 0;

    /* Zero pad the message to ensure it fits nicely in a DATA bus sized packet */
    while (message.length() % (DATA_BITS / 8) != 0) {
        message += '\0';
    }

    SC_METHOD(transmit);
    sensitive << clk.pos();
}

/* Destructor */
AvalonMaster::~AvalonMaster()
{
    std::cout << std::flush;
}

static uint32_t idx = 0;
void AvalonMaster::transmit()
{
    if (ready.read() == 1 && idx < message.length()) {
        std::cout << "Transmitting..." << std::endl;
        valid.write(1);
        binaryPacket = 0;

        for (int i = 0; i < DATA_BITS / 8; ++i) {
            binaryPacket |= (static_cast<binMessageType>(message[idx + i]) << (8 * i));
        }

        data.write(binaryPacket);
        idx += DATA_BITS / 8;
    }

    else {
        valid.write(0);
    }
}