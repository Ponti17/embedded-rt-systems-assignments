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
    std::cout << std::flush;  // Flush the output buffer
}

/* Thread */
void TCP_Consumer::mainThread() 
{
    while (true) 
    {
        wait(10, SC_MS); 
    }
}