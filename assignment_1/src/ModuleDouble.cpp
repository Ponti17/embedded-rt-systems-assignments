/*
 * ModuleDouble.cpp
 * Date Created: 29/08/24
*/

#include "ModuleDouble.hpp"

/* Constructor */
ModuleDouble::ModuleDouble(sc_module_name name) 
    : sc_module(name), moduleName(name)
{
    /* Register two threads */
    SC_THREAD(thread_A);
    SC_THREAD(thread_B);

    /* Register one method */
    SC_METHOD(method_A);
    sensitive << event_A 
              << event_B;
}

/* Destructor */
ModuleDouble::~ModuleDouble()
{
    std::cout << std::flush;
}

/* Thread A
 * Notifes event A every 3 ms
*/
void ModuleDouble::thread_A()
{
    while (true)
    {
        std::cout << "Thread A - Time: " << sc_time_stamp() << " - Notifying event_A\n";
        event_A.notify();

        wait(3, SC_MS);
        if (event_Aack.triggered())
        {
            std::cout << "Thread A - Time: " << sc_time_stamp() << " - Received event_Aack\n";
        }
        else
        {
            std::cout << "Thread A - Time: " << sc_time_stamp() << " - Timeout on event_A\n";
        }
    }
}

/* Thread B
 * Notifes event B every 2 ms
*/
void ModuleDouble::thread_B()
{
    while (true)
    {
        std::cout << "Thread B - Time: " << sc_time_stamp() << " - Notifying event_B\n";
        event_B.notify();

        wait(2, SC_MS);
        if (event_Back.triggered())
        {
            std::cout << "Thread B - Time: " << sc_time_stamp() << " - Received event_Back\n";
        }
        else
        {
            std::cout << "Thread B - Time: " << sc_time_stamp() << " - Timeout on event_B\n";
        }
    }
}

/* Method A
 * Alternates between waiting on event_A and event_B
*/
void ModuleDouble::method_A()
{
    if (event_A.triggered())
    {
        std::cout << "Method A - Time: " << sc_time_stamp() << " - Handling event_A\n";
        event_Aack.notify();
        next_trigger(event_B);
    }
    else if (event_B.triggered())
    {
        std::cout << "Method A - Time: " << sc_time_stamp() << " - Handling event_B\n";
        event_Back.notify();
        next_trigger(event_A);
    }
}