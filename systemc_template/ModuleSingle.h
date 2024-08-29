#ifndef MODULE_SINGLE_H // include guard to prevent double inclusion of header
#define MODULE_SINGLE_H

#include <systemc>		// include systemc library
#include <iostream>		// include iostream library to use cout (printing to console)
#include <string>		// include string library to use string data type

//class Modulesingle, inheriting from sc_module (parent class)
class ModuleSingle : public sc_module {

//Public access specifier, members are accessible from outside the class
public:

	//Constructor of the class ModuleSingle, taking a sc_module_name as argument. 
	ModuleSingle(sc_module_name name) : sc_module(name), moduleName(name)
	{

		//Register the thread
		SC_THREAD(moduleSingleThread);

	}

	//Destructor of the class ModuleSingle
	~ModuleSingle()
	{

		//Remember to flush the output buffer before the object is destroyed (console output buffer)
		std::cout << std::flush;

	}

//private access specifier, members are only accessible from within the class
private:

	//main thread of the class, started by the constructor
	void moduleSingleThread()
	{

		while (true)
		{
			// "this->" is a pointer referencing the object to itself, meaning we can use it to access the member variables and functions of the object
			// print the counter and simulation time
			this->printCounterAndSimulationTime();

			// increment the counter
			this->incrementCounter();

			// wait for 2 milliseconds
			wait(2, SC_MS);

		}

	}

	//Pretty straightforward function, increments the counter
	void incrementCounter()
	{
		//preincrements are faster than post-increments, so use pre-increments when possible. (No copying of the variable is needed, but watch out when using in loops)
		++this->counter;

	}

	//Prints the counter and the simulation time
	void printCounterAndSimulationTime() const
	{
		//we don't use std::cout here but \n to print a newline character, this is faster than std::endl and we flush the buffer upon destruction of the object.
		//Should not be used when multithreading with multiple threads writing to the same buffer.
		std::cout << "Counter: " << this->counter << " at time " << sc_time_stamp() << "\n";

	}

	//uints can be declared in binary, octal, decimal or hexadecimal format.
	sc_uint<4> counter = 0b0000;
	//same as the above, but in hexadecimal format
	sc_uint<4> counterHex = 0x0;
	//same as the above, but in decimal. The value stored in registers are the same. 
	sc_uint<4> counterDec = 0;

	// A placeholder for the name of the module, upon assignment. If we had multiple objects, we wouldnt have to manage naming on printing from the outside of the class.
	std::string moduleName;

};

#endif