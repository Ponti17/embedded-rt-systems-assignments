/*
 * TCP_Consumer.cpp
 * Date Created: 02/09/24
*/

#include "TCP_Consumer.hpp"

/* Constructor */
TCP_Consumer::TCP_Consumer(sc_module_name name) 
    : sc_module(name), moduleName(name)
{
    /* Register a thread process */
    SC_THREAD(mainThread);
}

/* Destructor */
TCP_Consumer::~TCP_Consumer() 
{
    std::cout << std::flush;
}

/* Thread */
void TCP_Consumer::mainThread() 
{
    while (true) 
    {
        TCPHeader* packet = in->read();

        std::cout << moduleName << ": received packet from port " << packet->SourcePort
                  << " - time: " << sc_time_stamp() << '\n';

        /* Free memory allocated for the packet */
        delete packet;
    }
}