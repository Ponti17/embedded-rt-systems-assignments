/************************************************************************/
/*	@file display_demo.c												*/
/*	@created 29/12/24													*/
/************************************************************************/

/* Includes */
#include "display_demo.h"
#include "display_ctrl.h"
#include <stdio.h>
#include "xuartps.h"
#include "math.h"
#include <ctype.h>
#include <stdlib.h>
#include "xil_types.h"
#include "xil_cache.h"
#include "timer_ps/timer_ps.h"
#include "xparameters.h"
#include "xgpu.h"
#include "cl.hpp"

/* XPAR redefines */
#define DYNCLK_BASEADDR     XPAR_AXI_DYNCLK_0_S_AXI_LITE_BASEADDR
#define VGA_VDMA_ID         XPAR_AXIVDMA_0_DEVICE_ID
#define DISP_VTC_ID         XPAR_VTC_0_DEVICE_ID
#define VID_VTC_IRPT_ID     XPS_FPGA3_INT_ID
#define VID_GPIO_IRPT_ID    XPS_FPGA4_INT_ID
#define SCU_TIMER_ID        XPAR_SCUTIMER_DEVICE_ID
#define UART_BASEADDR       XPAR_PS7_UART_1_BASEADDR
#define XGPU_DEVICE_ID      XPAR_XGPU_0_DEVICE_ID

/* Instances */
DisplayCtrl dispCtrl;
XAxiVdma vdma;
XGpu GpuInstance;

/* Framebuffers */
u8  frameBuf[DISPLAY_NUM_FRAMES][DEMO_MAX_FRAME] __attribute__((aligned(0x20)));
u8 *pFrames[DISPLAY_NUM_FRAMES];

/* Command list for each framebuffer */
u32 cl[DISPLAY_NUM_FRAMES][256] __attribute__((aligned(0x20)));
u32 *cl_ptr[DISPLAY_NUM_FRAMES];

/* GPU Commands */
#define BLIT_RECT_CMD  0x01
#define SET_CLIP_CMD   0x0002

/* Prototypes */
void InitGPU();
void GPU_BindFrameBuffer(u32 frameBufferAddr);
void GPU_BindCommandList(u32 commandListAddr);
void GPU_Start();
void GPU_WaitForDone();

void Error_Handler();
void PrintStartup();

struct cl_type** cls;

int main(void)
{
    int Status;
    XAxiVdma_Config *vdmaConfig;
    XGpu_Config 	*gpuConfig;

    cls = init_cl();

    /* Initialize CLs to all zeros */
    memset(cl[0], 0, sizeof(cl[0]));
    memset(cl[1], 0, sizeof(cl[1]));

    /* Initialize frame buffers to black */
    memset(frameBuf[0], 0xFF000000, sizeof(frameBuf[0]));
    memset(frameBuf[1], 0xFF000000, sizeof(frameBuf[1]));

    /* Pointers to both frame buffers and command lists  */
    int i;
    for (i = 0; i < DISPLAY_NUM_FRAMES; i++) {
        pFrames[i] = frameBuf[i];
        cl_ptr[i] = cl[i];
    }

    /* Peripherals */
    TimerInitialize(SCU_TIMER_ID);

    vdmaConfig = XAxiVdma_LookupConfig(VGA_VDMA_ID);
    if (!vdmaConfig) {
        Error_Handler("XAxiVdma_LookupConfig");
    }

    Status = XAxiVdma_CfgInitialize(&vdma, vdmaConfig, vdmaConfig->BaseAddress);
    if (Status != XST_SUCCESS) {
        Error_Handler("XAxiVdma_CfgInitialize");
    }

    Status = DisplayInitialize(&dispCtrl, &vdma, DISP_VTC_ID, DYNCLK_BASEADDR, pFrames, DEMO_STRIDE);
    if (Status != XST_SUCCESS) {
        Error_Handler("DisplayInitialize");
    }

    Status = DisplayStart(&dispCtrl);
    if (Status != XST_SUCCESS) {
        Error_Handler("DisplayStart");
    }

    gpuConfig = XGpu_LookupConfig(XGPU_DEVICE_ID);
    if (gpuConfig == NULL) {
        Error_Handler("XGpu_LookupConfig");
    }

    Status = XGpu_CfgInitialize(&GpuInstance, gpuConfig);
    if (Status != XST_SUCCESS) {
        Error_Handler("XGpu_CfgInitialize");
    }

    /* Set resolution to 1920x1080 */
    DisplayStop(&dispCtrl);
    DisplaySetMode(&dispCtrl, &VMODE_1920x1080);
    DisplayStart(&dispCtrl);

    PrintStartup();

    int nextFrame = 0;
    while (1) {
        nextFrame = dispCtrl.curFrame + 1;
        if (nextFrame >= DISPLAY_NUM_FRAMES) {
            nextFrame = 0;
        }
        gpu_draw(dispCtrl.framePtr[nextFrame]);
        DisplayChangeFrame(&dispCtrl, nextFrame);
    }

    return 0;
}

void GPU_BindFrameBuffer(u32 frameBufferAddr)
{
    XGpu_Set_frameBuffer_V(&GpuInstance, frameBufferAddr);
}

void GPU_BindCommandList(u32 commandListAddr)
{
    XGpu_Set_cl_V(&GpuInstance, commandListAddr);
}

void GPU_Start()
{
    XGpu_Set_status_V(&GpuInstance, 0xFFFFFFFF);
    XGpu_Start(&GpuInstance);
}

void GPU_WaitForDone()
{
    while (!XGpu_IsDone(&GpuInstance)) {}
}

void Error_Handler(const char* caller)
{
    if (caller != NULL) {
        xil_printf("Error occured during: %s\r\n", caller);
    }
    else {
    xil_printf("Error occurred.\r\n");
    }
    while (1) {}
}

void gpu_draw(u8 *frame)
{
    // Grab the pointer to the command list
    struct cl_type *myCL = cls[0];

    /****************************************************/
    /* 1) Handle the color transitions                  */
    /****************************************************/
    static u8 val = 0;
    static u8 r = 0;
    static u8 g = 0;
    static u8 b = 0;
    u8 speed = 16;

    switch (val) {
        case 0: // Red -> Yellow: Increase G
            if (g + speed >= 255) { g = 255; val = 1; } else { g += speed; }
            break;
        case 1: // Yellow -> Green: Decrease R
            if (r <= speed) { r = 0; val = 2; } else { r -= speed; }
            break;
        case 2: // Green -> Cyan: Increase B
            if (b + speed >= 255) { b = 255; val = 3; } else { b += speed; }
            break;
        case 3: // Cyan -> Blue: Decrease G
            if (g <= speed) { g = 0; val = 4; } else { g -= speed; }
            break;
        case 4: // Blue -> Magenta: Increase R
            if (r + speed >= 255) { r = 255; val = 5; } else { r += speed; }
            break;
        case 5: // Magenta -> Red: Decrease B
            if (b <= speed) { b = 0; val = 0; } else { b -= speed; }
            break;
        default:
            val = 0;
            break;
    }

    u32 color = (0xFF << 24) | (r << 16) | (g << 8) | b;

    clear_cl(myCL);

    // 1) Red
    draw_rect(myCL, 100, 100, 500, 500, 0xFFFF0000);

    // 2) Greenish
    draw_rect(myCL, 350, 350, 500, 500, 0x7F00FF00);

    // 3) The color-changing square
    draw_rect(myCL, 1000, 500, 600, 400, color);

    /****************************************************/
    /* 4) Flush caches, bind, and run the GPU           */
    /****************************************************/
    Xil_DCacheFlushRange((UINTPTR)frame, DEMO_MAX_FRAME);
    Xil_DCacheFlushRange((UINTPTR)myCL->array, 256);

    GPU_BindCommandList((u32)myCL->array);
    XGpu_Set_frameBuffer_V(&GpuInstance, (u32)frame);
    XGpu_Set_status_V(&GpuInstance, 0xFFFFFFFF);
    XGpu_Start(&GpuInstance);

    while (!XGpu_IsDone(&GpuInstance)) {
        // optional wait
    }

    // Final flush, if needed
    Xil_DCacheFlushRange((UINTPTR)myCL->array, 256);
    Xil_DCacheFlushRange((UINTPTR)frame, DEMO_MAX_FRAME);
}

void PrintStartup()
{
    xil_printf("\x1B[H"); 	// Set cursor to top left of terminal
    xil_printf("\x1B[2J"); 	// Clear terminal
    xil_printf("**************************************************\n\r");
    xil_printf("*                  ZYBO CONSOLE	                *\n\r");
    xil_printf("**************************************************\n\r");
    xil_printf("*Display Resolution: %28s*\n\r", dispCtrl.vMode.label);
    printf("*Display Pixel Clock Freq. (MHz): %15.3f*\n\r", dispCtrl.pxlFreq);
}
