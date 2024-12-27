#include <stdio.h>
#include <string.h>
#include <ap_int.h>

#define FB_SIZE 1920*1080
#define FIFO_SIZE 256

#define CMD_NONE        0x0000
#define BLIT_RECT_CMD   0x0001
#define BLIT_CIRC_CMD   0x0002
#define BLIT_LINE_CMD   0x0003

/**
 * The GPU function processes commands from the command FIFO.
 * 
 * @param fb_addr The address of the framebuffer
 * @param status The status flag to enable/disable processing
 * @param cmd_fifo The command FIFO
 * 
 * During runtime the CPU will set the address of the framebuffer to be drawn.
 * The CPU will calculate the scene and send the commands to the GPU.
 * The status flag will enable/disable processing.
 */
void gpu(ap_uint<32> fb_addr, ap_uint<8> status, ap_uint<32> cmd_fifo[256]) {
#pragma HLS INTERFACE s_axilite port=status
#pragma HLS INTERFACE m_axi port=fb_addr offset=slave
#pragma HLS INTERFACE ap_fifo port=cmd_fifo depth=256

    // Check if processing is enabled via the status flag
    if (status & 1) {
        // Process commands from the FIFO
        for (int i = 0; i < 256; i++) {
            ap_uint<32> cmd = cmd_fifo[i];
            ap_uint<16> cmd_type = cmd & 0xFFFF; // Extract command type
            ap_uint<16> cmd_data = cmd >> 16;   // Extract additional data

            // Handle the command
            switch (cmd_type) {
                case BLIT_RECT_CMD:
                    std::cout << "Processing BLIT_RECT_CMD with data: " << cmd_data << std::endl;
                    break;
                case BLIT_CIRC_CMD:
                    std::cout << "Processing BLIT_CIRC_CMD with data: " << cmd_data << std::endl;
                    break;
                case BLIT_LINE_CMD:
                    std::cout << "Processing BLIT_LINE_CMD with data: " << cmd_data << std::endl;
                    break;
                default:
                    std::cout << "Unknown command: " << cmd_type << std::endl;
                    break;
            }
        }
    }
}
