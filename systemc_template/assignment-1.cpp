#include "systemc.h"


SC_MODULE(Test)
{

	SC_CTOR(Test)
	{

		SC_THREAD(main_thread);

	}

	void main_thread(void)
	{

		SC_REPORT_INFO("Hello SystemC World!", "Hello SystemC World!");

	}

};