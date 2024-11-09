/*
 * gpu.cpp
 * Date Created: 09/11/24
*/

#include "gpu.hpp"
#include "cl.hpp"

/* External function prototypes */
void error_handler(const char* message);

/* Private function prototypes */
void gpu_blit_rect();

void submit_cl()
{
    cl_type* cl = get_bound_cl();
    rewind_cl(*cl);
    sc_uint<16> cmd = cl->array[cl->idx] & 0xFFFF;

    switch (cmd) {
        case BLIT_RECT_CMD:
            std::cout << "BLIT_RECT_CMD" << std::endl;
            gpu_blit_rect();
            break;
        default:
            error_handler("Unknown command");
            break;
    }
}

void gpu_blit_rect()
{
    std::cout << "Blitting rectangle" << std::endl;
}