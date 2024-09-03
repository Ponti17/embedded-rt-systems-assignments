/*
 * TCP_Producer.hpp
 * Date Created: 02/09/24
*/

#ifndef TCP_PRODUCER_HPP
#define TCP_PRODUCER_HPP

#include "systemc.h"
#include "TCP.hpp"

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