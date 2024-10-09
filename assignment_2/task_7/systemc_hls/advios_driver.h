#ifndef _ADVIOS_DRIVER_H
#define _ADVIOS_DRIVER_H

#include <systemc.h>


SC_MODULE(advios_driver){

	sc_in<bool> clk;
	sc_out<bool> reset;

	sc_out<sc_uint<4> > ctrl;
	sc_out<sc_uint<4> > outSwitch;
	sc_in<sc_uint<4> > inLeds;

	int retval;

	void test();
	inline void wait_c(int x);

	SC_CTOR(advios_driver){

		SC_CTHREAD(test, clk.pos());

	}

};

#endif
