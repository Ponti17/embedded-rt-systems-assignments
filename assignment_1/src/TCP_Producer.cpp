/*
 * TCP_Producer.cpp
 * Date Created: 02/09/24
*/

#include "TCP_Producer.hpp"

/* Constructor */
TCP_Producer::TCP_Producer(sc_module_name name) 
    : sc_module(name), moduleName(name)
{
    std::srand(std::time(nullptr));

    /* Register a thread process */
    SC_THREAD(mainThread);

    /* Register a method process */
    SC_METHOD(transmit);
    sensitive << event_transmit;
    dont_initialize();
}

/* Destructor */
TCP_Producer::~TCP_Producer() 
{
    std::cout << std::flush;  // Flush the output buffer
}

/* Thread */
void TCP_Producer::mainThread() 
{
    uint8_t wait_ms = 0;
    while (true) 
    {
        wait(wait_ms, SC_MS); 
        event_transmit.notify();
        wait_ms = std::rand() % 10;
    }
}

/* Transmit TCP package method */
void TCP_Producer::transmit() 
{
    std::cout << "Time: " << sc_time_stamp() << " - Transmitting..." << std::endl;
}