/*
 * TCP_Producer.hpp
 * Date Created: 02/09/24
*/

#ifndef TCP_PRODUCER_HPP
#define TCP_PRODUCER_HPP

#include "systemc.h"
#include <iostream>
#include <string>
#include <ctime>

/**
 * TCP typedef and defines 
 * TODO: This typedef and its defines should maybe live in its own header?
*/
#define PACKET_SIZE 512
#define DATA_SIZE (PACKET_SIZE-20)
typedef struct
{
sc_uint<16> SourcePort;
sc_uint<16> DestinationPort;
sc_uint<32> SequenceNumber;
sc_uint<32> Acknowledge;
sc_uint<16> StatusBits;
sc_uint<16> WindowSize;
sc_uint<16> Checksum;
sc_uint<16> UrgentPointer;
char Data[DATA_SIZE];
} TCPHeader;

/* Class definition */
class TCP_Producer : public sc_module {
public:
    /* Port */
    sc_port<sc_fifo_out_if<TCPHeader*>, 0> out;

    /* Event */
    sc_event event_transmit;

    /* Constructor */
    TCP_Producer(sc_module_name name);

    // Destructor
    ~TCP_Producer();

private:
    std::string moduleName;
    void mainThread();
    void transmit();
};

#endif // TCP_PRODUCER_HPP