/*
 * AvalonSlave.cpp
 * Date Created: 29/08/24
*/

#include "AvalonSlave.hpp"

/* Constructor */
AvalonSlave::AvalonSlave(sc_module_name name) 
    : sc_module(name), moduleName(name)
{
    /* Register a thread process */
    SC_THREAD(mainThread);
}

/* Destructor */
AvalonSlave::~AvalonSlave()
{
    std::cout << std::flush;
}

/* Thread */
void AvalonSlave::mainThread()
{
    while (true)
    {
        wait(2, SC_MS);
    }
}