#include "systemc.h"
#include "Top.hpp"

int sc_main(int sc_argc, char* sc_argv[])
{

	Top top("top");

	sc_start(10, SC_US);

    return 0;
}