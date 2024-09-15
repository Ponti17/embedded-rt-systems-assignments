/*
 * ModuleDouble.cpp
 * Date Created: 29/08/24
*/

#include "ModuleSingle.hpp"

/* Constructor */
ModuleSingle::ModuleSingle(sc_module_name name) 
    : sc_module(name), moduleName(name), counter(0b0000)
{
    /* Register a thread process */
    SC_THREAD(moduleSingleThread);

    /* Register a method process */
    SC_METHOD(trigger);

    /* The method is sensitive to 'event' */
    sensitive << event;
}

/* Destructor */
ModuleSingle::~ModuleSingle() 
{
    std::cout << std::flush;
}

/* Thread */
void ModuleSingle::moduleSingleThread() 
{
    while (true) 
    {
        wait(2, SC_MS); 
        incrementCounter();
        event.notify();
    }
}

void ModuleSingle::incrementCounter() 
{
    ++counter;
}

/* Trigger */
void ModuleSingle::trigger() 
{
    std::cout << "Module " << moduleName << " - Counter: " << counter
              << " at time " << sc_time_stamp() << "\n";
}
