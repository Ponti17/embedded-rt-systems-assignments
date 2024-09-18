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
    std::ofstream out("output.txt");
    out << message;
    out.close();
}

uint8_t packetsReceived = 0;
void AvalonSlave::receive() {

    if (packetsReceived > 7) {
        ready.write(0);
        packetsReceived = 0;
    }
    else {
        ready.write(1);
    }

    if (valid.read() == 1) {
        std::cout << "RECEIVING" << std::endl;
        binaryPacket = data.read();

        for (int i = 0; i < DATA_BITS / 8; ++i) {
            message += (binaryPacket >> 8 * i) & 0xFF;
        }

        ++packetsReceived;
    }

    if (valid.read() == 0) {
        std::cout << message << std::endl;
    }
}