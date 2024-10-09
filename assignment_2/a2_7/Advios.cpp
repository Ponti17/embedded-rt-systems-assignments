#include "advios.h"

void advios::iosThread() {

#pragma HLS RESOURCE variable=ctrl core=AXI4LiteS metadata="-bus_bundle slv0"

	control = 0x0;
	switchs = 0x0;
	sec_counter = 0x0;
	wait();

    while (true) {
        wait(); // Wait for clock event
        control = ctrl.read();
        switchs = inSwitch.read();

        switch (control){

        case 0x0:

        	if (switchs == 0x8) {

        		outLeds.write(0x0);
        		sec_counter = 0x0;

        	}else{

        		if(sec_pulse.read()){

        			sec_counter++;
        			outLeds.write(sec_counter);
        		}

        	}

        	break;
        default:
        	outLeds.write(control & switchs);
        	break;
        }
    }
}

void advios::countThread() {

	wait();
	count = 0;
    while (true) {
        wait();  // Wait for clock event
        count++;
        if (count == 100000000) {
        	sec_pulse.write(true);
        	count = 0;
        } else {
        	sec_pulse.write(false);
        }
    }
}
