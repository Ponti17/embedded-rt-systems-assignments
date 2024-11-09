/*
 * gpu.cpp
 * Date Created: 09/11/24
*/

#include "gpu.hpp"
#include "cl.hpp"
#include "fb.hpp"

/* External function prototypes */
void error_handler(const char* message);

/* Private function prototypes */
void gpu_blit_rect(cl_type cl);

static fb_type* bound_fb = nullptr;

void submit_cl()
{
    cl_type* cl = get_bound_cl();
    rewind_cl(*cl);
    sc_uint<16> cmd = cl->array[cl->idx] & 0xFFFF;

    switch (cmd) {
        case BLIT_RECT_CMD:
            std::cout << "BLIT_RECT_CMD" << std::endl;
            gpu_blit_rect(*cl);
            break;
        default:
            error_handler("Unknown command");
            break;
    }
}

void bind_fb(fb_type* fb)
{
    bound_fb = fb;
}

void gpu_blit_rect(cl_type cl)
{
    sc_uint<16> x = cl.array[cl.idx] >> 16;
    sc_uint<16> y = cl.array[cl.idx + 1] & 0xFFFF;
    sc_uint<16> w = cl.array[cl.idx + 1] >> 16;
    sc_uint<16> h = cl.array[cl.idx + 2] & 0xFFFF;
    sc_uint<32> color = cl.array[cl.idx + 3];

    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
    std::cout << "w: " << w << std::endl;
    std::cout << "h: " << h << std::endl;
    std::cout << "color: " << color << std::endl;

    for (int y_idx = y; y_idx < y+h; ++y_idx) {
        int idx = y_idx * 400;
        for (int x_idx = x; x_idx < x+w; ++x_idx) {
            bound_fb->fb_array[idx + x_idx] = color;
        }
    }
}