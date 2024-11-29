#include <stdio.h>
#include <ap_int.h>
#include <iomanip>

#include "cl.hpp"
#include "gpu.hpp"
#include "fb.hpp"

#define FB_SIZE 1920*1080
#define CL_SIZE 512

void gpu(ap_uint<32> frameBuffer[FB_SIZE], ap_uint<32> cl[CL_SIZE], ap_uint<8> status);

int main()
{
	/* Initialize the GPU */
	ap_uint<16> RESX = 800;
	ap_uint<16> RESY = 400;
	ap_uint<16> STRIDE = RESX * 4;
	gpu_init(STRIDE, RESX, RESY);

	fb_type* fb1 = allocate_fb(RESX, RESY, BGRA8888);

	/* Create command list instance */
    cl_type cl_instance;

    /* Create command list of size */
	int size = CL_SIZE;
    create_cl(cl_instance, size);

	/* Bind command list */
	bind_cl(cl_instance);

	/* Bind FB */
	bind_fb(fb1);

	/* Blit black background */
	blit_rect(0, 0, RESX, RESY, 0x000000FF);

	/* Blit red square */
	blit_rect(50, 50, 100, 100, 0x0000FFFF);

	/* Blit green square */
	blit_rect(50, 200, 200, 100, 0x00FF00FF);

	/* Blit blue square */
	blit_rect(200, 50, 100, 200, 0xFF0000FF);

	/* Blit cyan circle */
	blit_circ(600, 200, 100, 0xFFFF00FF);

	/* Blit yellow line */
	blit_line(300, 0, 500, 400, 20, 0x00FFFFFF);

	/* Print all 32-bit entries in cl_instance.array as 4-byte hex */
	/* Be vary of leading 0 */
    for (ap_uint<32> i = 0; i < cl_instance.cl_size; ++i) {
        std::cout << "Entry " << i << ": 0x" 
                  << std::hex << std::uppercase 
                  << cl_instance.cl_array[i] << std::endl;
    }

    gpu(fb1->fb_array, cl_instance.cl_array, 1);

    /* Delete the cl_instance */
    delete_cl(cl_instance);

    return 0;
}
