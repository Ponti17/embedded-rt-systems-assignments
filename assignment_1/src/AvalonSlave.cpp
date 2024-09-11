/*
 * AvalonSlave.cpp
 * Date Created: 29/08/24
*/

#include "AvalonSlave.hpp"

/* Constructor */
AvalonSlave::AvalonSlave(sc_module_name name) : sc_module(name), moduleName(name) {
    message = "";
    binaryPacket = 0;

    /* Register a thread process */
    SC_METHOD(receive);
    sensitive << clk.pos();
}

/* Destructor */
AvalonSlave::~AvalonSlave() {
    std::cout << std::flush;
}

void AvalonSlave::receive() {

    ready.write(1);

    if (valid.read() == 1) {
        std::cout << "RECEIVING" << std::endl;
        binaryPacket = data.read();

        for (int i = 0; i < DATA_BITS / 8; ++i) {
            message += (binaryPacket >> 8 * i) & 0xFF;
        }
    }

    if (valid.read() == 0) {
        std::cout << message << std::endl;
    }
}