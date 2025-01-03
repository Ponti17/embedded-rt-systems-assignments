/************************************************************************/
/*	@file display_demo.c												*/
/*	@created 29/12/24													*/
/************************************************************************/

/* Includes */
#include <stdio.h>
#include "math.h"
#include <ctype.h>
#include <stdlib.h>

#include "xuartps.h"
#include "xil_types.h"
#include "xil_cache.h"
#include "xparameters.h"
#include "xgpu.h"
#include "xgpio.h"

#include "cl.h"
#include "display_demo.h"
#include "display_ctrl/display_ctrl.h"
#include "timer_ps/timer_ps.h"

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
DisplayCtrl dispCtrl;       /* Display Controller Instance          */
XAxiVdma vdma;              /* VDMA Instance                        */
XGpu GpuInstance;           /* GPU Instance                         */
XGpio PushInstance;			/* Push buttons Instance 				*/

/* Framebuffers */
u8  frameBuf[DISPLAY_NUM_FRAMES][DEMO_MAX_FRAME] __attribute__((aligned(0x20)));
u8 *pFrames[DISPLAY_NUM_FRAMES];

/* Prototypes */
void InitGPU();
void GPU_BindFrameBuffer(u32 frameBufferAddr);
void GPU_BindCommandList(u32 commandListAddr);
void GPU_Start();
void GPU_WaitForDone();
int GpioInit(XGpio *GpioInstancePtr, u16 DeviceId);

void Error_Handler();
void PrintStartup();
u32 RainbowRGB();

struct cl_type** cls;

#define STILL 		0x00
#define MOVE_UP 	0x01
#define MOVE_DOWN 	0x02

int main(void)
{
    int Status;
    XAxiVdma_Config *vdmaConfig;
    XGpu_Config 	*gpuConfig;

    cls = init_cl();

    /* Initialize frame buffers to black */
    memset(frameBuf[0], 0xFF000000, sizeof(frameBuf[0]));
    memset(frameBuf[1], 0xFF000000, sizeof(frameBuf[1]));

    /* Pointers to both frame buffers and command lists  */
    int i;
    for (i = 0; i < DISPLAY_NUM_FRAMES; i++) {
        pFrames[i] = frameBuf[i];
    }

    /* Peripherals */
    GpioInit(&PushInstance, XPAR_AXI_GPIO_BTN_DEVICE_ID);

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

    u32 move = STILL;
    int nextFrame = 0;
    while (1) {
        nextFrame = dispCtrl.curFrame + 1;
        if (nextFrame >= DISPLAY_NUM_FRAMES) {
            nextFrame = 0;
        }

        DisplayChangeFrame(&dispCtrl, dispCtrl.curFrame);
        int btn_read = XGpio_DiscreteRead(&PushInstance, 1);
        switch (btn_read) {
            case 1:
                move = MOVE_UP;
                break;
            case 2:
                move = MOVE_DOWN;
                break;
            default:
            	move = STILL;
                break;
        }

        gpu_draw(dispCtrl.framePtr[nextFrame], nextFrame, move);
        dispCtrl.curFrame = nextFrame;
    }

    return 0;
}

void gpu_draw(u8 *frame, int frameIndex, u32 move)
{
    // Grab the pointer to the command list
    struct cl_type *myCL = cls[frameIndex];

    static int square_x = 200;
    static int square_y = 200;
    static int x_dir = 2;
    static int y_dir = 2;

    static int prev_x_0 = 0;
    static int prev_y_0 = 0;
    static int prev_x_1 = 0;
    static int prev_y_1 = 0;

    if (move == MOVE_DOWN && !(square_y + 200 >= 1080)) {
        square_y += y_dir;
    }
    else if (move == MOVE_UP && !(square_y <= 0)) {
        square_y -= y_dir;
    }

    rewind_cl(myCL);
    if (frameIndex) {
    	draw_rect(myCL, prev_x_0, prev_y_0, 200, 200, 0xFF000000);
    	prev_x_0 = square_x;
    	prev_y_0 = square_y;
    } else {
    	draw_rect(myCL, prev_x_1, prev_y_1, 200, 200, 0xFF000000);
    	prev_x_1 = square_x;
    	prev_y_1 = square_y;
    }

    u32 color = RainbowRGB();
    draw_rect(myCL, square_x, square_y, 200, 200, color);

    draw_stop(myCL);

    /****************************************************/
    /* 4) Flush caches, bind, and run the GPU           */
    /****************************************************/
    Xil_DCacheFlushRange((UINTPTR)myCL->array, 256);
    Xil_DCacheFlushRange((UINTPTR)frame, DEMO_MAX_FRAME);

    GPU_BindCommandList((u32)myCL->array);
    GPU_BindFrameBuffer((u32)frame);
    GPU_Start();

    Xil_DCacheFlushRange((UINTPTR)myCL->array, 256);
    Xil_DCacheFlushRange((UINTPTR)frame, DEMO_MAX_FRAME);
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

u32 RainbowRGB()
{
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

    return color;
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

/*****************************************************************************/
/**
* Initializes a GPIO instance as an input device.
*
* @param GpioInstancePtr is a pointer to the instance of XGpio driver.
* @param DeviceId is the device Id of the GPIO device.
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
******************************************************************************/
int GpioInit(XGpio *GpioInstancePtr, u16 DeviceId)
{
	XGpio_Initialize(GpioInstancePtr, DeviceId);
	XGpio_SetDataDirection(GpioInstancePtr, 1, 0xffffffff);

	return XST_SUCCESS;
}
