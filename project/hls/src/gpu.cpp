#include <stdio.h>
#include <string.h>
#include <ap_int.h>

#define FB_SIZE 1920*1080
#define FIFO_SIZE 256

#define CMD_NONE        0x0000
#define BLIT_RECT_CMD   0x0001
#define BLIT_CIRC_CMD   0x0002
#define BLIT_LINE_CMD   0x0003

/* Prototypes */
void gpu_blit_rect(
    ap_uint<32> frameBuffer[FB_SIZE],
    ap_uint<16> arg0,
    ap_uint<16> arg1,
    ap_uint<16> arg2,
    ap_uint<16> arg3,
    ap_uint<16> arg4,
    ap_uint<16> arg5,
    ap_uint<16> arg6
    );

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
 * 
 * The CMD FIFO has a depth of 256 with each entry being 32 bits.
 * A single command takes a fixed size of 4 entries i.e. 128 bits.
 */
void gpu(ap_uint<32> frameBuffer[FB_SIZE], ap_uint<8> status, ap_uint<32> cmd_fifo[256]) {
#pragma HLS INTERFACE s_axilite port=status
#pragma HLS INTERFACE m_axi port=fb_addr offset=slave
#pragma HLS INTERFACE ap_fifo port=cmd_fifo depth=256

    // Check if processing is enabled via the status flag
    if (status & 1) {
        // Process commands from the FIFO
        for (int i = 0; i < 256/4; i++) {
            ap_uint<32> dword_0 = cmd_fifo[i*4];
            ap_uint<32> dword_1 = cmd_fifo[i*4+1];
            ap_uint<32> dword_2 = cmd_fifo[i*4+2];
            ap_uint<32> dword_3 = cmd_fifo[i*4+3];
            ap_uint<16> cmd = dword_0 & 0xFFFF;     // Extract command type
            ap_uint<16> arg0 = dword_0 >> 16;       // Extract arguments
            ap_uint<16> arg1 = dword_1 & 0xFFFF;
            ap_uint<16> arg2 = dword_1 >> 16;
            ap_uint<16> arg3 = dword_2 & 0xFFFF;
            ap_uint<16> arg4 = dword_2 >> 16;
            ap_uint<16> arg5 = dword_3 & 0xFFFF;
            ap_uint<16> arg6 = dword_3 >> 16;

            // Handle the command
            switch (cmd) {
                case BLIT_RECT_CMD:
                    std::cout << "Processing BLIT_RECT_CMD" << std::endl;
                    gpu_blit_rect(frameBuffer, arg0, arg1, arg2, arg3, arg4, arg5, arg6);
                    break;
                case BLIT_CIRC_CMD:
                    std::cout << "Processing BLIT_CIRC_CMD" << std::endl;
                    break;
                case BLIT_LINE_CMD:
                    std::cout << "Processing BLIT_LINE_CMD" << std::endl;
                    break;
                default:
                    std::cout << "Unknown command: " << cmd << std::endl;
                    break;
            }
        }
    }
}

void gpu_blit_rect(
    ap_uint<32> frameBuffer[FB_SIZE],
    ap_uint<16> arg0,
    ap_uint<16> arg1,
    ap_uint<16> arg2,
    ap_uint<16> arg3,
    ap_uint<16> arg4,
    ap_uint<16> arg5,
    ap_uint<16> arg6
    ) {
    ap_uint<16> x = arg0;
    ap_uint<16> y = arg1;
    ap_uint<16> w = arg2;
    ap_uint<16> h = arg3;
    ap_uint<32> color = (ap_uint<32>(arg6) << 16) | arg5;

    std::cout << "arg5: " << std::hex << arg5 << std::endl;
    std::cout << "arg6: " << std::hex << arg6 << std::endl;
    std::cout << "color: " << std::hex << color << std::endl;

    std::cout << "x: " << x << std::endl;
    std::cout << "y: " << y << std::endl;
    std::cout << "w: " << w << std::endl;
    std::cout << "h: " << h << std::endl;

    for (int y_idx = y; y_idx < y+h; ++y_idx) {
        int idx = y_idx * 1920;
        for (int x_idx = x; x_idx < x+w; ++x_idx) { 
            frameBuffer[idx + x_idx] = color;
        }
    }
}
