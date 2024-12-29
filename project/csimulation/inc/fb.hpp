/*
 * fb.hpp
 * Date Created: 09/11/24
*/

#ifndef FB_HPP
#define FB_HPP

#include "systemc.h"
#include <iostream>
#include <string>
#include "cl.hpp"

/* Color formats */
#define BGRA8888 0x01

struct fb_type {
    sc_uint<16> stride = 0;
    sc_uint<16> height = 0;
    sc_uint<16> width  = 0;
    sc_uint<32> *fb_array = nullptr;
};

/**
 * Allocate a frame buffer
 * @param width Width
 * @param height Height
 * @param format Format
 * @return fb_type* Frame buffer
 */
fb_type* allocate_fb(sc_uint<16> width, sc_uint<16> height, sc_uint<8> format);

/**
 * Save a frame buffer as an image
 * @param fb Frame buffer
 * @param filename Filename
 * @return void
 */
void save_fb_as_image(fb_type* fb, const std::string& filename);

#endif // FB_HPP
