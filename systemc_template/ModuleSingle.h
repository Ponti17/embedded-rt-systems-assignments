#ifndef MODULE_SINGLE_H
#define MODULE_SINGLE_H

#include <systemc>
#include <iostream>
#include <string>

class ModuleSingle : public sc_module {

public:
	ModuleSingle(sc_module_name name) : sc_module(name), moduleName(name)
	{

		SC_THREAD(moduleSingleThread);

	}

	~ModuleSingle()
	{

		std::cout << std::flush;

	}


private:

	void moduleSingleThread()
	{

		while (true)
		{

			this->printCounterAndSimulationTime();

			this->incrementCounter();

			wait(2, SC_MS);

		}

	}

	void incrementCounter()
	{

		++this->counter;

	}

	void printCounterAndSimulationTime() const
	{

		std::cout << "Counter: " << this->counter << " at time " << sc_time_stamp() << "\n";

	}

	sc_uint<4> counter = 0b0000;
	std::string moduleName;

};


#endif

