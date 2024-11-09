#include "systemc.h"
#include "cl.hpp"
#include "gpu.hpp"
#include "fb.hpp"
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
	fb_type* fb1 = allocate_fb(400, 400, BGRA8888);

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

	/* Bind FB */
	bind_fb(fb1);

	blit_rect(0x32, 0x32, 0x64, 0x64, 0x0000FFFF);

	/* Print all 32-bit entries in cl_instance.array as 4-byte hex */
	/* Be vary of leading 0 */
    for (int i = 0; i < cl_instance.size; ++i) {
        std::cout << "Entry " << i << ": 0x" 
                  << std::hex << std::uppercase 
                  << cl_instance.array[i] << std::endl;
    }

	/* Submit the command list */
	submit_cl();

	save_fb_as_image(fb1, "framebuffer_image.png");

    /* Delete the cl_instance */
    delete_cl(cl_instance);
}

void error_handler(const char* message)
{
	std::cerr << message << std::endl;
	exit(1);
}