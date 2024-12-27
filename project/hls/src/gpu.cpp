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
#pragma HLS INTERFACE s_axilite port=return bundle=control
#pragma HLS INTERFACE s_axilite port=status bundle=control
#pragma HLS INTERFACE m_axi port=frameBuffer offset=slave
#pragma HLS INTERFACE ap_fifo port=cmd_fifo depth=256

    // Check if processing is enabled via the status flag
    if (status & 1) {
        // Process commands from the FIFO
        for (int i = 0; i < 256/4; i++) {
            ap_uint<32> dword_0 = cmd_fifo[i*4];
            ap_uint<32> dword_1 = cmd_fifo[i*4+1];
            ap_uint<32> dword_2 = cmd_fifo[i*4+2];
            ap_uint<32> dword_3 = cmd_fifo[i*4+3];
            ap_uint<16> cmd  = dword_0 & 0xFFFF;    // Extract command type
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

    ap_uint<8> newB = color.range(31, 24);
    ap_uint<8> newG = color.range(23, 16);
    ap_uint<8> newR = color.range(15, 8);
    ap_uint<8> newA = color.range(7, 0);

    std::cout << "newB: " << std::hex << newB << std::endl;
    std::cout << "newG: " << std::hex << newG << std::endl;
    std::cout << "newR: " << std::hex << newR << std::endl;
    std::cout << "newA: " << std::hex << newA << std::endl;

    bool print_once = true;
    for (int y_idx = y; y_idx < y+h; ++y_idx) {
        int idx = y_idx * 1920;
        for (int x_idx = x; x_idx < x+w; ++x_idx) {
            #pragma HLS PIPELINE II=1
            int fb_index = idx + x_idx;

            ap_uint<32> oldColor = frameBuffer[fb_index];
            ap_uint<8> oldB = oldColor.range(31, 24);
            ap_uint<8> oldG = oldColor.range(23, 16);
            ap_uint<8> oldR = oldColor.range(15, 8);
            ap_uint<8> oldA = oldColor.range(7, 0);

            /* If alpha is 100% just overwrite fully */
            if (newA == 0xFF) {
                frameBuffer[fb_index] = color;
            }
            /* If alpha is 0% do nothing */
            else if (newA == 0) {
            }
            /* Blend */
            else {
                ap_uint<16> outB_16 = ( (255 - newA) * oldB + newA * newB ) >> 8;
                ap_uint<16> outG_16 = ( (255 - newA) * oldG + newA * newG ) >> 8;
                ap_uint<16> outR_16 = ( (255 - newA) * oldR + newA * newR ) >> 8;

                /**
                 * Set out alpha as the maximum of the two alphas.
                 * This does not make sense, but it works?
                 */
                ap_uint<8> outA = (oldA > newA) ? oldA : newA;

                ap_uint<32> outColor = 
                    (ap_uint<32>(outA)    << 0)   |
                    (ap_uint<32>(outR_16) << 8)   |
                    (ap_uint<32>(outG_16) << 16)  |
                    (ap_uint<32>(outB_16) << 24);

                if (print_once) {
                    std::cout << "oldB: " << std::hex << oldB << std::endl;
                    std::cout << "oldG: " << std::hex << oldG << std::endl;
                    std::cout << "oldR: " << std::hex << oldR << std::endl;
                    std::cout << "oldA: " << std::hex << oldA << std::endl;

                    std::cout << "outB_16: " << std::hex << outB_16 << std::endl;
                    std::cout << "outG_16: " << std::hex << outG_16 << std::endl;
                    std::cout << "outR_16: " << std::hex << outR_16 << std::endl;
                    std::cout << "outA: " << std::hex << outA << std::endl;

                    std::cout << "outColor: " << std::hex << outColor << std::endl;
                    print_once = false;
                }
                
                frameBuffer[fb_index] = outColor;
            }
        }
    }
}