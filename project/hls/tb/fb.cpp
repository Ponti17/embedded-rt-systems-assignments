/*
 * fb.cpp
 * Date Created: 09/11/24
 * 
 * DESCRIPTION:
 * This file contains the implementation for the frame buffer API.
 * 
 * A frame buffer is a memory buffer that holds the pixel data for a frame.
 * The stride is the number of bytes in a row of pixels.
 * 
 * A helper function is provided to save the frame buffer as an image.
*/

#include "fb.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define __STDC_LIB_EXT1__
#include "stb_image_write.h"
#include <ap_int.h>

/* External function prototypes */
void error_handler(const char* message);

/**
 * Allocate a frame buffer
 * A frame buffer is a memory buffer that holds the pixel data for a frame.
 */
fb_type* allocate_fb(ap_uint<16> width, ap_uint<16> height, ap_uint<8> format)
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

    fb->fb_array = new ap_uint<32>[fb->stride * height]();

    return fb;
}

void save_fb_as_image(fb_type* fb, const std::string& filename)
{
    // Create a vector for the image data in the correct format (BGRA to RGBA).
    std::vector<unsigned char> image_data(fb->width * fb->height * 4);

    // Convert from BGRA to RGBA format
    for (int y = 0; y < fb->height; ++y) {
        for (int x = 0; x < fb->width; ++x) {
            int idx = y * fb->width + x;
            ap_uint<32> pixel = fb->fb_array[idx];

            // Extract BGRA components from the pixel
            unsigned char b = static_cast<unsigned char>((pixel >> 24) & 0xFF); // Blue
            unsigned char g = static_cast<unsigned char>((pixel >> 16) & 0xFF); // Green
            unsigned char r = static_cast<unsigned char>((pixel >> 8) & 0xFF);  // Red
            unsigned char a = static_cast<unsigned char>(0xFF); // Alpha

            // Set the corresponding RGBA value in the image data
            int img_idx = (y * fb->width + x) * 4;
            image_data[img_idx + 0] = r; // Red
            image_data[img_idx + 1] = g; // Green
            image_data[img_idx + 2] = b; // Blue
            image_data[img_idx + 3] = a; // Alpha
        }
    }

    // Use stb_image_write to save the image in PNG format
    if (!stbi_write_png(filename.c_str(), fb->width, fb->height, 4, image_data.data(), fb->width * 4)) {
        std::cerr << "Error: Unable to write image to file: " << filename << std::endl;
    }
}