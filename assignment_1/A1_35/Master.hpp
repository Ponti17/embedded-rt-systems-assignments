#pragma once

#include <systemc.h>
#include "defs.hpp"

class Master : public sc_module {

public:

    sc_fifo_out<sc_uint<8>> out_fifo;

    Master(sc_module_name name);

private:

    void generateDataForAdapter();

};

