/*
 * gpu.cpp
 * Date Created: 09/11/24
 * 
 * DESCRIPTION:
 * This file contains a software model of the GPU.
 * 
 * Ideally this should be converted to a somewhat accurate SystemC model.
 * 
 * The GPU can have one bound command list at a time.
 * 
 * The command submit_cl() will execute all commands in the bound command list.
 * Note that submitting will "rewind" the command list i.e. the index will be reset.
 * 
 * The GPU can also have one bound framebuffer at a time. This framebuffer will be
 * the target of all blit commands.
*/

#include "gpu.hpp"
#include "cl.hpp"
#include "fb.hpp"
#include <ap_int.h>

/* External function prototypes */
void error_handler(const char* message);

/* Private function prototypes */
void gpu_blit_rect(cl_type& cl);
void gpu_blit_circ(cl_type& cl);
void gpu_blit_line(cl_type& cl);

static fb_type* bound_fb = nullptr;

void submit_cl()
{
    cl_type& cl = get_bound_cl();
    rewind_cl(cl);

    while (cl.idx < cl.size) {
        ap_uint<16> cmd = cl.array[cl.idx] & 0xFFFF;

        switch (cmd) {
            case BLIT_RECT_CMD:
                std::cout << "BLIT_RECT_CMD" << std::endl;
                gpu_blit_rect(cl);
                break;
            case BLIT_CIRC_CMD:
                std::cout << "BLIT_CIRC_CMD" << std::endl;
                gpu_blit_circ(cl);
                break;
            case BLIT_LINE_CMD:
                std::cout << "BLIT_LINE_CMD" << std::endl;
                gpu_blit_line(cl);
                break;
            case CMD_NONE:
                std::cout << "CMD_NONE" << std::endl;
                goto exit_loop;
                break;
            default:
                error_handler("Unknown command");
                break;
        }
    }
    exit_loop: ;
}

void bind_fb(fb_type* fb)
{
    bound_fb = fb;
}

ap_uint<32> read_cl(cl_type& cl)
{
    return cl.array[cl.idx++];
}

/**
 * Blits a rectangle to the framebuffer.
 * Loops through all pixels in the bounding box of the rectangle
 * and sets the pixel to the specified color.
 * Only for demonstration purposes.
 */
void gpu_blit_rect(cl_type& cl)
{
    ap_uint<32> dword_0 = read_cl(cl);
    ap_uint<32> dword_1 = read_cl(cl);
    ap_uint<32> dword_2 = read_cl(cl);
    ap_uint<32> dword_3 = read_cl(cl);
    ap_uint<16> x = dword_0 >> 16;
    ap_uint<16> y = dword_1 & 0xFFFF;
    ap_uint<16> w = dword_1 >> 16;
    ap_uint<16> h = dword_2 & 0xFFFF;
    ap_uint<32> color = dword_3;

#ifdef DEBUG_GPU
    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
    std::cout << "w: " << w << std::endl;
    std::cout << "h: " << h << std::endl;
    std::cout << "color: " << color << std::endl;
#endif

    for (int y_idx = y; y_idx < y+h; ++y_idx) {
        int idx = y_idx * bound_fb->width;
        for (int x_idx = x; x_idx < x+w; ++x_idx) {
            bound_fb->fb_array[idx + x_idx] = color;
        }
    }
}

/**
 * Blits a circle to the framebuffer.
 * Loops through all pixels in the bounding box of the circle
 * and checks if the pixel is inside the circle.
 * Only for demonstration purposes.
 */
void gpu_blit_circ(cl_type& cl)
{
    ap_uint<32> dword_0 = read_cl(cl);
    ap_uint<32> dword_1 = read_cl(cl);
    ap_uint<32> dword_2 = read_cl(cl);
    ap_uint<16> x = dword_0 >> 16;
    ap_uint<16> y = dword_1 & 0xFFFF;
    ap_uint<16> r = dword_1 >> 16;
    ap_uint<32> color = dword_2;

#ifdef DEBUG_GPU
    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
    std::cout << "r: " << r << std::endl;
    std::cout << "color: " << color << std::endl;
#endif

    for (int y_idx = y-r; y_idx < y+r; ++y_idx) {
        int idx = y_idx * bound_fb->width;
        for (int x_idx = x-r; x_idx < x+r; ++x_idx) {
            if ((x_idx - x) * (x_idx - x) + (y_idx - y) * (y_idx - y) < r * r) {
                bound_fb->fb_array[idx + x_idx] = color;
            }
        }
    }
}

/**
 * Uses DDA algorithm to draw a line.
 * Super slow, uses floating point arithmetic.
 * Thickness not implemented.
 * Only for demonstration purposes.
 */
void gpu_blit_line(cl_type& cl)
{
    ap_uint<32> dword_0 = read_cl(cl);
    ap_uint<32> dword_1 = read_cl(cl);
    ap_uint<32> dword_2 = read_cl(cl);
    ap_uint<32> dword_3 = read_cl(cl);
    ap_uint<16> x0 = dword_0 >> 16;
    ap_uint<16> y0 = dword_1 & 0xFFFF;
    ap_uint<16> x1 = dword_1 >> 16;
    ap_uint<16> y1 = dword_2 & 0xFFFF;
    ap_uint<16> t = dword_2 >> 16;
    ap_uint<32> color = dword_3;

#ifdef DEBUG_GPU
    std::cout << "x0: " << x0 << std::endl;
    std::cout << "y0: " << y0 << std::endl;
    std::cout << "x1: " << x1 << std::endl;
    std::cout << "y1: " << y1 << std::endl;
    std::cout << "t: " << t << std::endl;
    std::cout << "color: " << color << std::endl;
#endif

    int dx = x1 - x0;
    int dy = y1 - y0;
    int steps = abs(dx) > abs(dy) ? abs(dx) : abs(dy);
    float x_inc = dx / (float)steps;
    float y_inc = dy / (float)steps;
    float x = x0;
    float y = y0;

    for (int i = 0; i <= steps; ++i) {
        int idx = (int)y * bound_fb->width + (int)x;
        bound_fb->fb_array[idx] = color;
        x += x_inc;
        y += y_inc;
    }
}