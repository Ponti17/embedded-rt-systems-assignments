#include "advios.hpp"
#include <systemc.h>

#define CLOCK_PERIOD 5
#define CLOCK_PERIOD_UNIT SC_NS

SC_MODULE(AdviosTestBench)
{
	sc_signal<bool> clk;
	sc_signal<bool> reset;
	sc_signal<sc_uint<NUM_BITS>> ctrl;
	sc_signal<sc_uint<NUM_BITS>> inSwitch;
	sc_signal<sc_uint<NUM_BITS>> outLeds;

	Advios* deviceUnderTest;

	void clock()
	{
		std::cout << "Clock started" << std::endl;
		while (true)
		{
			clk.write(false);
			wait(CLOCK_PERIOD, CLOCK_PERIOD_UNIT);
			clk.write(true);
			wait(CLOCK_PERIOD, CLOCK_PERIOD_UNIT);
		}
	}

	void stimulus()
	{
		// Test reset signal
		reset.write(true);
		waitForXCycles(4);
		reset.write(false);
		waitForXCycles(20);

		/**
		 * CASE 1, increment leds
		 * control state = 0x0
		 * switches != 0x8
		 */

		ctrl.write(0x0);
		inSwitch.write(0x0);
		waitForXCycles(100);

		/**
		 * CASE 2, reset leds
		 * control state = 0x0
		 * switches = 0x8
		 */
		
		inSwitch.write(0x8);
		waitForXCycles(20);

		/**
		 * CASE 3, outLeds are masked by control state.
		 * combinations tested (wait 4 clocks between each test):
		 * CTRL			SWITCH		RESULT (expected)
		 * 0b0001		0b0001		0b0001
		 * 0b0010		0b0010		0b0010
		 * 0b0100		0b0100		0b0100
		 * 0b1000		0b1000		0b1000
		 * 0b1111		0b1010		0b1010
		 * 0b1111		0b0101		0b0101
		 */
		
		ctrl.write(0b0001);
		inSwitch.write(0b0001);
		waitForXCycles(4);

		ctrl.write(0b0010);
		inSwitch.write(0b0010);
		waitForXCycles(4);

		ctrl.write(0b0100);
		inSwitch.write(0b0100);
		waitForXCycles(4);

		ctrl.write(0b1000);
		inSwitch.write(0b1000);
		waitForXCycles(4);

		ctrl.write(0b1111);
		inSwitch.write(0b1010);
		waitForXCycles(4);

		ctrl.write(0b1111);
		inSwitch.write(0b0101);
		waitForXCycles(4);

		sc_stop();
	}

	inline void waitForXCycles(int cycles)
	{
		for (int i = 0; i < cycles; i++)
		{
			wait(clk.posedge_event());
		}
	}

	SC_CTOR(AdviosTestBench)
	{
		deviceUnderTest = new Advios("advios");

		deviceUnderTest->clk(clk);
		deviceUnderTest->reset(reset);
		deviceUnderTest->ctrl(ctrl);
		deviceUnderTest->inSwitch(inSwitch);
		deviceUnderTest->outLeds(outLeds);

		SC_THREAD(clock);
		SC_THREAD(stimulus);
	}

	~AdviosTestBench()
	{
		delete deviceUnderTest;
	}
};

int sc_main(int argc, char* argv[])
{
	std::cout << "Initiating test-bench" << std::endl;
	AdviosTestBench test("test");
	std::cout << "Starting simulation" << std::endl;
	sc_start(); 
	return 0;
}
