#include "stimulus.hpp"

std::vector<int> a_values{ 3,5,7,9 };
std::vector<int> b_values{ 2,4,6,8 };


Stimulus::Stimulus(sc_module_name name) : sc_module(name)
{

	SC_THREAD(generateStimulus);
	sensitive << clk.pos();

}

void Stimulus::generateStimulus()
{

	for (int i = 0; i < a_values.size(); i++)
	{

		wait();
		this->a.write(a_values[i]);
		this->b.write(b_values[i]);

	}

}


