/*
 * TCP_Consumer.hpp
 * Date Created: 02/09/24
*/

#ifndef TCP_CONSUMER_HPP
#define TCP_CONSUMER_HPP

#include "systemc.h"
#include <iostream>
#include <string>

class TCP_Consumer : public sc_module {

public:
    /* Constructor */
    TCP_Consumer(sc_module_name name);

    // Destructor
    ~TCP_Consumer();

private:
    std::string moduleName;
    void mainThread();
};

#endif // TCP_CONSUMER_HPP