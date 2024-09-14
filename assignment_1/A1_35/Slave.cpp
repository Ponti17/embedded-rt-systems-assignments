#include "Slave.hpp"

Slave::Slave(sc_module_name name)
{
	SC_METHOD(receive);
	sensitive << clock.pos();
}

void Slave::receive()
{

	if (reset.read() == SC_LOGIC_0) {

		if (valid.read() == SC_LOGIC_1) {

			std::cout << "Slave received: " << data.read() << std::endl;

			ready.write(SC_LOGIC_1);

		} else {

			ready.write(SC_LOGIC_0);

		}

	}

}
