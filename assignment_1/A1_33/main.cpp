#include "systemc.h"
#include "TCP_Producer.hpp"
#include "TCP_Consumer.hpp"

#define SIMULATION_TIME 100
#define SIMULATION_TIME_UNIT SC_MS

int sc_main(int sc_argc, char* sc_argv[])
{
    /**
     * Initialize and configure FIFOs and modules
     */
    sc_fifo<TCPHeader*> fifo1(10);
    sc_fifo<TCPHeader*> fifo2(10);

    // Create instance of the SystemC module
    TCP_Producer producer("producer");
    TCP_Consumer consumer_1("consumer_1");
    TCP_Consumer consumer_2("consumer_2");

    producer.out.bind(fifo1);
    producer.out.bind(fifo2);

    consumer_1.in.bind(fifo1);
    consumer_2.in.bind(fifo2);

    // invoke the simulator
    sc_start(SIMULATION_TIME, SIMULATION_TIME_UNIT);
    std::cout << "Simulation finished at " << sc_time_stamp() << std::endl;
    return 0;
}