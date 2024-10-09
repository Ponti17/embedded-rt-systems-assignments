#ifndef ADVIOS_H
#define ADVIOS_H

#include <systemc.h>

SC_MODULE(advios){

	sc_in<bool> clk;
	sc_in<bool> reset;
	sc_in<sc_uint<4> > inSwitch;
	sc_in<sc_uint<4> > ctrl;
	sc_out<sc_uint<4> > outLeds;

	sc_uint<4> switchs;
	sc_uint<4> control;
	sc_uint<28> count;
	sc_uint<4> sec_counter;
	sc_signal<bool> sec_pulse;

	void iosThread();
	void countThread();

	SC_CTOR(advios){

		SC_CTHREAD(iosThread, clk.pos());
		reset_signal_is(reset, true);

		SC_CTHREAD(countThread, clk.pos());
		reset_signal_is(reset, true);

	}

};

#endif
