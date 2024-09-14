#include "Master.hpp"


Master::Master(sc_module_name name) : sc_module(name)
{
	SC_THREAD(generateDataForAdapter);
}


void Master::generateDataForAdapter() {

	sc_uint<8> data = 0;
	while (true)
	{

		wait(MASTER_OUTPUT_PERIOD, MASTER_OUTPUT_PERIOD_UNIT);
		out_fifo->write(data++);
		std::cout << "Master: Writing data " << data << " to FIFO at " << sc_time_stamp() <<  std::endl;
	}

}
