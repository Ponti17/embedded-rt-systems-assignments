/*
 * fb.cpp
 * Date Created: 09/11/24
*/

#include "fb.hpp"

/* External function prototypes */
void error_handler(const char* message);

/**
 * Allocate a frame buffer
 * A frame buffer is a memory buffer that holds the pixel data for a frame.
 */
fb_type* allocate_fb(sc_uint<16> width, sc_uint<16> height, sc_uint<8> format)
{
    fb_type* fb = new fb_type();
    fb->width = width;
    fb->height = height;

    switch (format) {
        case BGRA8888:
            fb->stride = width * 4;
            break;
        default:
            error_handler("Unknown format");
            break;
    }

    fb->fb_array = new sc_uint<32>[fb->stride * height]();
    return fb;
}
