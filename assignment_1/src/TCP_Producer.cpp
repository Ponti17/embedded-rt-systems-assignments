/*
 * TCP_Producer.cpp
 * Date Created: 02/09/24
*/

#include "TCP_Producer.hpp"

/* Constructor */
TCP_Producer::TCP_Producer(sc_module_name name) 
    : sc_module(name), moduleName(name)
{
    /* Initialize rand */
    srand(time(0));

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
        wait_ms = rand() % 9 + 2;
    }
}

/* Transmit TCP package method */
void TCP_Producer::transmit() 
{
    /* Allocate TCPHeader on heap and create a pointer, package, to it */
    TCPHeader* package = new TCPHeader();
    package->SourcePort         = 0;
    package->DestinationPort    = 0;
    package->SequenceNumber     = 0;    
    package->Acknowledge        = 0;
    package->StatusBits         = 0;
    package->WindowSize         = 0;
    package->Checksum           = 0;
    package->UrgentPointer      = 0;
    memset(package->Data, 0, DATA_SIZE);

    /**
     * Transmit to all FIFO channels.
     * TODO: We are somehow not entering this loop. Likely out.size() returns 0.
     */
    for (int i = 0; i < out.size(); i++)
    {
        out[i]->write(package);
    }

    std::cout << "Time: " << sc_time_stamp() << " - Transmitting..." << std::endl;
}