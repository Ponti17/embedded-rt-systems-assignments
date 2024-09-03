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
    TCPHeader* packet = new TCPHeader();
    packet->SourcePort         = 0;
    packet->DestinationPort    = 0;
    packet->SequenceNumber     = 0;    
    packet->Acknowledge        = 0;
    packet->StatusBits         = 0;
    packet->WindowSize         = 0;
    packet->Checksum           = 0;
    packet->UrgentPointer      = 0;
    memset(packet->Data, 0, DATA_SIZE);

    /**
     * Transmit to all FIFO channels.
     */
    for (int i = 0; i < out.size(); i++)
    {
        TCPHeader* packet_copy = new TCPHeader(*packet);
        packet_copy->DestinationPort = i;
        out[i]->write(packet_copy);
        std::cout << moduleName << ": transmitting packet to port " << packet_copy->DestinationPort
                  << " - time: " << sc_time_stamp() << '\n';
    }

    delete packet;
}