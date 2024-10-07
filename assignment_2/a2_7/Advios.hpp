#pragma once

#include <systemc.h>

#define NUM_BITS 4

class Advios :
    public sc_module
{

public:
	sc_in<bool> clk;
	sc_in<bool> reset;
	sc_in<sc_uint<NUM_BITS>> ctrl;
	sc_in<sc_uint<NUM_BITS>> inSwitch;
	sc_out<sc_uint<NUM_BITS>> outLeds;


	Advios(sc_module_name name);
	void generatePulse();
	void switchControl();

private:
	sc_signal<bool> pulse;

};

