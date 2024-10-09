/*
 * main.c
 * Date Created: 02/10/24
*/

#include "main.h"
#include "xparameters.h"
#include "xscutimer.h"
#include "xscugic.h"
#include "xil_exception.h"
#include "xil_printf.h"
#include "sleep.h"

/* Function Prototypes */
int ScuTimerInit(XScuTimer *TimerInstancePtr, u16 TimerDeviceId, u32 TimerCounter);

void TimerStart(XScuTimer *TimerInstancePtr);
void TimerStop(XScuTimer *TimerInstancePtr);
void TimerLoad(XScuTimer *TimerInstancePtr, u32 TimerCounter);

uint8_t rand_uint8(void);

/* Device Instances */
XScuTimer TimerInstance;	/* Cortex A9 Scu Private Timer Instance	*/

#define OFFSET_CTRL 0x14
#define CTRL_ADDR XPAR_ADVIOS_0_S_AXI_SLV0_BASEADDR + OFFSET_CTRL

int main (void) 
{
	ScuTimerInit(&TimerInstance, XPAR_XSCUTIMER_0_DEVICE_ID, 100*MILLISECOND);
	XScuTimer_Start(&TimerInstance);

	static uint8_t ctrl_read = 0;
	int input;

	xil_printf("\r\n-- Start of the Program --");

	while (1)
	{
		xil_printf("\r\n\nCMD:> ");
		input = inbyte();
		xil_printf("%c", input);
		switch (input)
		{
			case '0':
				xil_printf("\r\nReading CTRL: ");
				ctrl_read = Xil_In8(CTRL_ADDR) & 0xF;
				xil_printf("%u", ctrl_read);
				break;
			case '1':
				xil_printf("\r\nWriting 0x0.");
				Xil_Out8(CTRL_ADDR, 0x0);
				break;
			case '2':
				xil_printf("\r\nWriting 0xA.");
				Xil_Out8(CTRL_ADDR, 0xA);
				break;
			case '3':
				xil_printf("\r\nWriting 0xF.");
				Xil_Out8(CTRL_ADDR, 0xF);
				break;
			case '4':
				xil_printf("\r\nGenerating random value.");
				uint8_t rand = rand_uint8() & 0xF;
				xil_printf("\r\nWriting %u to CTRL.", rand);
				Xil_Out8(CTRL_ADDR, rand);
				break;
			default:
				xil_printf("\r\nUnrecognized input. \"%c\"", input);
				break;
		}
	}
}

/*****************************************************************************/
/**
* Initializes the timer. The timer is configured to reset on expiration
*
* @param TimerInstancePtr is a pointer to the instance of XScuTimer driver.
* @param TimerDeviceId is the device Id of the XScuTimer device.
* @param TimerCounter is the value to load into the timer counter register.
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
******************************************************************************/
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

/*****************************************************************************/
/**
* Starts the timer.
*
* @param TimerInstancePtr is a pointer to the instance of XScuTimer driver.
* @return None
******************************************************************************/
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

uint8_t rand_uint8()
{
    return (uint8_t) XScuTimer_GetCounterValue(&TimerInstance);
}
