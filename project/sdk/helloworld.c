#include <stdio.h>
#include "platform.h"
#include "xil_printf.h"
#include "xgpu.h"
#include "xscutimer.h"
#include "xscugic.h"
#include "xil_exception.h"
#include "xil_printf.h"

// Base address for the GPU IP - this should match the address defined in your hardware design
#define XGPU_DEVICE_ID  XPAR_XGPU_0_DEVICE_ID

XGpu GpuInstance;

// Function prototypes
int InitializeGPU();
void ConfigureGPU();
void StartGPU();
void WaitForCompletion();
void VerifyResults();

#define CL_ADDR	0x1F000000
#define FB_ADDR 0x10000000

#define CL_SIZE (256 * sizeof(u32))
#define FB_SIZE (1920 * 1080 * sizeof(u32))

//#define DDR_BASE XPAR_PS7_DDR_0_S_AXI_BASEADDR + 0x01000000
#define DDR_BASE 0x01000000

// Define command types
#define BLIT_RECT_CMD 0x01 // Example value; replace with actual command code as per your GPU IP specification
#define SET_CLIP_CMD   0x0002

// Define command array indices for clarity
#define CMD_INDEX_RED_START    0
#define CMD_INDEX_GREEN_START  4

/* Function Prototypes */
int ScuTimerInit(XScuTimer *TimerInstancePtr, u16 TimerDeviceId, u32 TimerCounter);
int ScuIntrInit(XScuGic *IntcInstancePtr, u16 GicDeviceId);
int TimerSetupIntr(XScuGic *IntcInstancePtr, XScuTimer *TimerInstancePtr, u16 TimerIntrId);

void TimerStart(XScuTimer *TimerInstancePtr);
void TimerStop(XScuTimer *TimerInstancePtr);
void TimerLoad(XScuTimer *TimerInstancePtr, u32 TimerCounter);
void TimerReinitialize(XScuTimer *TimerInstancePtr, u32 TimerCounter, void (*TimerFunction)(void));

XScuTimer TimerInstance;	/* Cortex A9 Scu Private Timer Instance	*/
XScuGic IntcInstance;		/* Interrupt Controller Instance 		*/

static void TimerIntrHandler(void *CallBackRef);
static void TimerDisableIntrSystem(XScuGic *IntcInstancePtr, u16 TimerIntrId);

/* Function pointer for the timer interrupt handler */
void (*TimerFunctionPtr)(void);

#define MILLISECOND 325000

int main()
{
    int status;

    // Initialize the platform (e.g., UART, interrupts)
    init_platform();

    volatile uint32_t* cl_array = (volatile uint32_t*)CL_ADDR;
    volatile uint32_t* fb_array = (volatile uint32_t*)DDR_BASE;

    memset((void*)cl_array, 0, CL_SIZE);
    memset((void*)fb_array, 0x00000000, FB_SIZE);

    ScuTimerInit(&TimerInstance, XPAR_XSCUTIMER_0_DEVICE_ID, 100*MILLISECOND);

    u32 x, y, w, h;
    // --- Red Square ---
    x = 100;
    y = 100;
    w = 500;
    h = 500;
    cl_array[CMD_INDEX_RED_START]     = ((x & 0xFFFF) << 16) | (BLIT_RECT_CMD & 0xFFFF);
    cl_array[CMD_INDEX_RED_START + 1] = ((w & 0xFFFF) << 16) | (y & 0xFFFF);
    cl_array[CMD_INDEX_RED_START + 2] = ((0 & 0xFFFF) << 16) | (h & 0xFFFF);
    cl_array[CMD_INDEX_RED_START + 3] = 0x0000FFFF;

    /* Green square alpha compositing */
    x = 350;
    y = 350;
    w = 500;
    h = 500;
    cl_array[CMD_INDEX_RED_START + 4] = ((x & 0xFFFF) << 16) | (BLIT_RECT_CMD & 0xFFFF);
    cl_array[CMD_INDEX_RED_START + 5] = ((w & 0xFFFF) << 16) | (y & 0xFFFF);
    cl_array[CMD_INDEX_RED_START + 6] = ((0 & 0xFFFF) << 16) | (h & 0xFFFF);
    cl_array[CMD_INDEX_RED_START + 7] = 0x00FF007F;

    /* Set clip */
    x = 0;
    y = 0;
    w = 1500;
    h = 1080;
    cl_array[CMD_INDEX_RED_START + 8] = ((x & 0xFFFF) << 16) | (SET_CLIP_CMD & 0xFFFF);
    cl_array[CMD_INDEX_RED_START + 9] = ((w & 0xFFFF) << 16) | (y & 0xFFFF);
    cl_array[CMD_INDEX_RED_START + 10] = ((0 & 0xFFFF) << 16) | (h & 0xFFFF);
    cl_array[CMD_INDEX_RED_START + 11] = 0x00000000;

    x = 700;
    y = 800;
    w = 2000;
    h = 200;
    cl_array[CMD_INDEX_RED_START + 12] = ((x & 0xFFFF) << 16) | (BLIT_RECT_CMD & 0xFFFF);
    cl_array[CMD_INDEX_RED_START + 13] = ((w & 0xFFFF) << 16) | (y & 0xFFFF);
    cl_array[CMD_INDEX_RED_START + 14] = ((0 & 0xFFFF) << 16) | (h & 0xFFFF);
    cl_array[CMD_INDEX_RED_START + 15] = 0xFF0000FF;

    // Initialize the GPU instance
    status = InitializeGPU();
    if (status != XST_SUCCESS) {
        xil_printf("GPU Initialization Failed\r\n");
        cleanup_platform();
        return XST_FAILURE;
    }
    xil_printf("GPU Initialized Successfully\r\n\n");

    // Configure the GPU with necessary parameters
    ConfigureGPU();

	volatile u32 start = 0;
	volatile u32 end = 0;

    // Start the GPU operation
    TimerReinitialize(&TimerInstance, 1000*MILLISECOND, NULL);
    start = XScuTimer_GetCounterValue(&TimerInstance);
    Xil_DCacheFlushRange((UINTPTR)fb_array, FB_SIZE);
    Xil_DCacheFlushRange((UINTPTR)cl_array, CL_SIZE);
    StartGPU();
    //xil_printf("GPU Operation Started\r\n");

    // Wait for the GPU to complete its operation
    WaitForCompletion();
    end = XScuTimer_GetCounterValue(&TimerInstance);
    xil_printf("Clock cycles: %llu\n", 2 * (start - end));
    xil_printf("GPU Operation Completed\r\n");

    // Retrieve and verify the results
    VerifyResults();

    // Optionally, you can handle interrupts here if implemented

    // Clean up the platform before exiting
    cleanup_platform();
    return XST_SUCCESS;
}

/**
 * Initialize the GPU instance by looking up the configuration and initializing it.
 */
int InitializeGPU()
{
    XGpu_Config *ConfigPtr;
    int status;

    // Look up the GPU configuration based on the device ID
    ConfigPtr = XGpu_LookupConfig(XGPU_DEVICE_ID);
    if (ConfigPtr == NULL) {
        xil_printf("No configuration found for GPU device ID %d\r\n", XGPU_DEVICE_ID);
        return XST_FAILURE;
    }

    // Initialize the GPU instance with the configuration
    status = XGpu_CfgInitialize(&GpuInstance, ConfigPtr);
    if (status != XST_SUCCESS) {
        xil_printf("Configuration Initialization Failed\r\n");
        return status;
    }

    return XST_SUCCESS;
}

/**
 * Configure the GPU with necessary parameters such as frame buffer address,
 * status, and other relevant configurations.
 */
void ConfigureGPU()
{
    // Example: Set the frame buffer address
    // Replace 0x10000000 with the actual address you intend to use
    XGpu_Set_frameBuffer_V(&GpuInstance, DDR_BASE);
    xil_printf("Frame Buffer Address Set to 0x%08X\r\n", XGpu_Get_frameBuffer_V(&GpuInstance));

    // Example: Set other parameters as needed
    XGpu_Set_cl_V(&GpuInstance, CL_ADDR);
    xil_printf("CL_V Set to 0x%08X\r\n", XGpu_Get_cl_V(&GpuInstance));

    // Example: Set status if required by your GPU IP
    XGpu_Set_status_V(&GpuInstance, 0xFFFFFFFF); // Example value
    xil_printf("Status Set to 0x%08X\r\n", XGpu_Get_status_V(&GpuInstance));
}

/**
 * Start the GPU operation.
 */
void StartGPU()
{
    // Start the GPU
    XGpu_Start(&GpuInstance);

    // Optionally, enable auto-restart if your application requires continuous processing
    // XGpu_EnableAutoRestart(&GpuInstance);
}

/**
 * Wait for the GPU operation to complete by polling the done status.
 */
void WaitForCompletion()
{
    // Poll the GPU until it signals completion
    while (!XGpu_IsDone(&GpuInstance)) {
        // Optionally, you can implement a timeout or sleep to reduce CPU usage
    }

    // Optionally, check if the GPU is idle
    if (XGpu_IsIdle(&GpuInstance)) {
        xil_printf("GPU is idle\r\n\n");
    }
}

/**
 * Retrieve and verify the results from the GPU.
 */
void VerifyResults()
{
    u32 frameBufferAddress;
    u32 statusValue;
    // u32 clValue; // Uncomment if you set and need to verify cl_V

    // Retrieve the frame buffer address
    frameBufferAddress = XGpu_Get_frameBuffer_V(&GpuInstance);
    xil_printf("Retrieved Frame Buffer Address: 0x%08X\r\n", frameBufferAddress);

    // Retrieve the status
    statusValue = XGpu_Get_status_V(&GpuInstance);
    xil_printf("Retrieved Status: 0x%08X\r\n", statusValue);

    // Retrieve other parameters if needed
    // clValue = XGpu_Get_cl_V(&GpuInstance);
    // xil_printf("Retrieved CL_V: 0x%08X\r\n", clValue);

    // TODO: Add verification logic based on your GPU IP's expected behavior
    // For example, compare the frame buffer address with expected value
    if (frameBufferAddress == DDR_BASE) {
        xil_printf("Frame Buffer Address Verification Passed\r\n");
    } else {
        xil_printf("Frame Buffer Address Verification Failed\r\n");
    }

    // Similarly, verify status and other parameters as needed
    if (statusValue == 0x00000001) { // Example expected value
        xil_printf("Status Verification Passed\r\n");
    } else {
        xil_printf("Status Verification Failed\r\n");
    }

    // Add more comprehensive verification based on GPU functionality
}

int ScuTimerInit(XScuTimer *TimerInstancePtr, u16 TimerDeviceId, u32 TimerCounter)
{
	XScuTimer_Config *ConfigPtr;
	int Status;

	ConfigPtr = XScuTimer_LookupConfig(TimerDeviceId);
	Status = XScuTimer_CfgInitialize(TimerInstancePtr, ConfigPtr, ConfigPtr->BaseAddr);
	if (Status != XST_SUCCESS)
	{
		xil_printf("Timer init failed.");
		return XST_FAILURE;
	}

	/* Enable Auto Reloading of Timer */
	XScuTimer_EnableAutoReload(TimerInstancePtr);

	/* Load timer counter register with default 1 second */
	XScuTimer_LoadTimer(TimerInstancePtr, 325000000);

	return XST_SUCCESS;
}

void TimerStart(XScuTimer *TimerInstancePtr)
{
	XScuTimer_Start(TimerInstancePtr);
}

void TimerStop(XScuTimer *TimerInstancePtr)
{
	XScuTimer_Stop(TimerInstancePtr);
}

void TimerLoad(XScuTimer *TimerInstancePtr, u32 TimerCounter)
{
	XScuTimer_LoadTimer(TimerInstancePtr, TimerCounter);
}

void TimerReinitialize(XScuTimer *TimerInstancePtr, u32 TimerCounter, void (*TimerFunction)(void))
{
	TimerStop(TimerInstancePtr);
	TimerFunctionPtr = TimerFunction;
	TimerLoad(TimerInstancePtr, TimerCounter);
	XScuTimer_RestartTimer(TimerInstancePtr);
	TimerStart(TimerInstancePtr);
}
