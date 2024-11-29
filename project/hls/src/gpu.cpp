#include <stdio.h>
#include <string.h>
#include <ap_int.h>

#define FB_SIZE 1920*1080
#define CL_SIZE 512

#define CMD_NONE        0x0000
#define BLIT_RECT_CMD   0x0001
#define BLIT_CIRC_CMD   0x0002
#define BLIT_LINE_CMD   0x0003

void gpu(ap_uint<32> frameBuffer[FB_SIZE], ap_uint<32> cl[CL_SIZE], ap_uint<8> status) {
#pragma HLS INTERFACE s_axilite port=status
#pragma HLS INTERFACE m_axi port=frameBuffer offset=slave
#pragma HLS INTERFACE m_axi port=cl offset=slave

    int i;
    int cl_buff[CL_SIZE];

    if (status & 1) {
        for (i = 0; i < CL_SIZE; i++) {
            cl_buff[i] = cl[i];
        }

        for (i = 0; i < 64; i++) {
            ap_uint<16> cmd = cl_buff[i] & 0xFFFF;
            std::cout << "cmd: " << cmd << std::endl;
        }
    }
}
