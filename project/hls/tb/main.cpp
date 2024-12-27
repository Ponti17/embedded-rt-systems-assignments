#include <stdio.h>
#include <ap_int.h>
#include <iostream>
#include <string>
#include <vector>

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

/* Defines */
#define FB_SIZE 1920*1080
#define BGRA8888 0x01

#define CL_SIZE 		512
#define CMD_NONE        0x0000
#define BLIT_RECT_CMD   0x0001
#define BLIT_CIRC_CMD   0x0002
#define BLIT_LINE_CMD   0x0003

/* Structs */
struct fb_type {
    ap_uint<16> stride;
    ap_uint<16> height;
    ap_uint<16> width;
    ap_uint<32> *fb_array;
};

/* Prototypes */
fb_type* allocate_fb(ap_uint<16> width, ap_uint<16> height, ap_uint<8> format);
void save_fb_as_image(fb_type* fb, const std::string& filename);

void gpu(ap_uint<32> fb_addr, ap_uint<8> status, ap_uint<32> cmd_fifo[256]);

int main()
{
	/* Initialize FB */
    ap_uint<16> RESX = 1920;
	ap_uint<16> RESY = 1080;
	ap_uint<16> STRIDE = RESX * 4;
    fb_type* fb1 = allocate_fb(RESX, RESY, BGRA8888);

    // Initialize command FIFO with sample data
    ap_uint<32> cmd_fifo[256];
    for (int i = 0; i < 256; i++) {
        cmd_fifo[i] = 0;
    }
    cmd_fifo[0] = (BLIT_RECT_CMD & 0xFFFF) | (0x4321 << 16); // BLIT_RECT_CMD with data 0x4321
    cmd_fifo[1] = (BLIT_CIRC_CMD & 0xFFFF) | (0x8765 << 16); // BLIT_CIRC_CMD with data 0x8765
    cmd_fifo[2] = (BLIT_LINE_CMD & 0xFFFF) | (0xCBA9 << 16); // BLIT_LINE_CMD with data 0xCBA9

    // Call the GPU function
    ap_uint<8> status = 1; // Enable processing
    gpu(fb1->fb_array, status, cmd_fifo);

    save_fb_as_image(fb1, "framebuffer_image.png");

    return 0;
}

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
