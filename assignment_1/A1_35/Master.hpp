#pragma once

#include <systemc.h>
#include "defs.hpp"

class Master : public sc_module {

public:

    sc_fifo_out<sc_int<8>> out_fifo;

	// Use SC_HAS_PROCESS when needing more than module name at instantiation
    SC_HAS_PROCESS(Master);
    Master(sc_module_name name);

private:

    void generateDataForAdapter();

};

