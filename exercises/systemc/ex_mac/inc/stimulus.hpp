#pragma once

#include "systemc.h"

class Stimulus : public sc_module
{
public:
	Stimulus(sc_module_name name);
	sc_in <bool> clk;
	sc_out<int> a, b;

private:
	

	void generateStimulus();

};