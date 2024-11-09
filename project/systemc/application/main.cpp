#include "systemc.h"
#include "cl.hpp"
#include <iomanip>

/* Function Prototypes */
void cl_test(void);

int sc_main(int sc_argc, char* sc_argv[])
{
	cl_test();
	return 0;
}

void cl_test()
{
	/* Initialize the GPU */
	sc_uint<16> RESX = 400;
	sc_uint<16> RESY = 400;
	sc_uint<16> STRIDE = 400 * 4;
	gpu_init(STRIDE, RESX, RESY);

	/* Create command list instance */
    cl_type cl_instance;

    /* Create command list of size 16 */
	int size = 16;
    create_cl(cl_instance, size);

	/* Bind command list */
	bind_cl(cl_instance);

	blit_rect(0x32, 0x32, 0x64, 0x64, 0xFAFAFAFA);

	/* Print all 32-bit entries in cl_instance.array as 4-byte hex */
	/* Be vary of leading 0 */
    for (int i = 0; i < cl_instance.size; ++i) {
        std::cout << "Entry " << i << ": 0x" 
                  << std::hex << std::uppercase 
                  << cl_instance.array[i] << std::endl;
    }

    /* Delete the cl_instance */
    delete_cl(cl_instance);
}

void error_handler(const char* message)
{
	std::cerr << message << std::endl;
	exit(1);
}