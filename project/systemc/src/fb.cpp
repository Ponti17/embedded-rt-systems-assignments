/*
 * fb.cpp
 * Date Created: 09/11/24
*/

#include "fb.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <cassert>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#define __STDC_LIB_EXT1__
#include "stb_image_write.h"

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

    // Set the entire frame buffer to blue
    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            int idx = y * width + x;
            fb->fb_array[idx] = (0xFF000000); // Blue channel set to 255, others set to 0
        }
    }

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
            sc_uint<32> pixel = fb->fb_array[idx];

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