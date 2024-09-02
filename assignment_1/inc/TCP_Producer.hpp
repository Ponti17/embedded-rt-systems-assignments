/*
 * TCP_Producer.hpp
 * Date Created: 02/09/24
*/

#ifndef TCP_PRODUCER_HPP
#define TCP_PRODUCER_HPP

#include "systemc.h"
#include <iostream>
#include <string>

class TCP_Producer : public sc_module {

public:
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