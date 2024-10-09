#include "advios_driver.h"

void advios_driver::test(){

	wait();
	reset.write(true);
	ctrl.write(0x0);
	outSwitch.write(0x0);
	wait_c(3);

	reset.write(false);
	wait();

	//test ctrl 0x1-0xf and in switch
	//expected behavior inLeds = ctrl AND outLeds
	sc_uint<4> leds_result;
	bool mask_result = true;
	for (sc_uint<4> i_ctrl = 0x1; i_ctrl < 0xF; i_ctrl++) {
	    for (sc_uint<4> i_outSwitch = 0x0; i_outSwitch < 0xF; i_outSwitch++) {
	        ctrl.write(i_ctrl);
	        outSwitch.write(i_outSwitch);
	        std::cout << "i_ctrl: " << i_ctrl.to_uint() << " i_outSwitch: " << i_outSwitch.to_uint() << std::endl;

	        wait_c(2);  // Wait for two clock cycles to allow signal propagation

	        leds_result = inLeds.read();

	        if (!(leds_result == (i_outSwitch & i_ctrl))) {
	            mask_result = false;
	        }
	    }
	}

	wait_c(10);
	//test ctrl = 0x0
	bool counter_result = true;
	ctrl.write(0x0);
	reset.write(true);
	wait();
	reset.write(false);
	for(sc_uint<4> i_outSwitch = 0x0; i_outSwitch < 0xf; i_outSwitch++){
		outSwitch.write(i_outSwitch);
		for (int i = 0; i < 16; i++){
			wait();

		}
	}


	retval = 0;
	std::cout << "Test results\n"
			<< "CTRL = 0x1 -> 0xF, Switches = 0x0 -> 0xf"
			<< "\tPassed status: " << mask_result
			<< std::endl;
}

inline void advios_driver::wait_c(int x){

	for (int i = 0; i < x; i++){
		wait();
	}

}
