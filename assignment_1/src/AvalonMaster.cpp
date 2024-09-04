/*
 * AvalonMaster.cpp
 * Date Created: 29/08/24
*/

#include "AvalonMaster.hpp"

/* Constructor */
AvalonMaster::AvalonMaster(sc_module_name name) 
    : sc_module(name), moduleName(name)
{
    /* Register a thread process */
    SC_THREAD(mainThread);
}

/* Destructor */
AvalonMaster::~AvalonMaster()
{
    std::cout << std::flush;
}

/* Thread */
void AvalonMaster::mainThread()
{
    while (true)
    {
        wait(2, SC_MS);
    }
}