/**
#include "systemc.h"
#include "ModuleSingle.h"

SC_MODULE(Hello_SystemC) {  // declare module class

    // create a constructor
    SC_CTOR(Hello_SystemC) {

        // register the process
        SC_THREAD(main_thread);
    }

    void main_thread(void) {

        SC_REPORT_INFO("Hello SystemC World!", "Hello SystemC World!");
    }
};

int sc_main(int sc_argc, char* sc_argv[]) {

    // create an instance of the SystemC module
    Hello_SystemC HelloWorld_i("HelloWorld_i");

    // invoke the simulator
    sc_start();
    return 0;
}
**/