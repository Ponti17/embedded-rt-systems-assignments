/*
 * ModuleDouble.cpp
 * Date Created: 29/08/24
*/

#include "ModuleDouble.hpp"

/* Constructor */
ModuleDouble::ModuleDouble(sc_module_name name) 
    : sc_module(name), moduleName(name)
{
    /* Register a thread process */
    SC_THREAD(moduleDoubleThread);
}

/* Destructor */
ModuleDouble::~ModuleDouble()
{
    std::cout << std::flush;
}

/* Thread */
void ModuleDouble::moduleDoubleThread()
{
    while (true)
    {
        wait(2, SC_MS);
    }
}