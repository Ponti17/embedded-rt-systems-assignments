/*
 * main.c
 * Date Created: 02/10/24
*/

#include "main.h"
#include "xparameters.h"
#include "xgpio.h"
#include "xscutimer.h"
#include "xscugic.h"
#include "xil_exception.h"
#include "xil_printf.h"
#include "led_ip.h"
#include "sleep.h"
#include "matrixMultiplication.h"

/* Function Prototypes */
int ScuTimerInit(XScuTimer *TimerInstancePtr, u16 TimerDeviceId, u32 TimerCounter);
int ScuIntrInit(XScuGic *IntcInstancePtr, u16 GicDeviceId);
int TimerSetupIntr(XScuGic *IntcInstancePtr, XScuTimer *TimerInstancePtr, u16 TimerIntrId);
int GpioInit(XGpio *GpioInstancePtr, u16 DeviceId);

void TimerStart(XScuTimer *TimerInstancePtr);
void TimerStop(XScuTimer *TimerInstancePtr);
void TimerLoad(XScuTimer *TimerInstancePtr, u32 TimerCounter);
void TimerReinitialize(XScuTimer *TimerInstancePtr, u32 TimerCounter, void (*TimerFunction)(void));

static void TimerIntrHandler(void *CallBackRef);
static void TimerDisableIntrSystem(XScuGic *IntcInstancePtr, u16 TimerIntrId);

void read_switches();
void count_leds();
void matrix_soft();
void matrix_hard();

/* Device Instances */
XScuTimer TimerInstance;	/* Cortex A9 Scu Private Timer Instance	*/
XScuGic IntcInstance;		/* Interrupt Controller Instance 		*/
XGpio DipInstance;			/* Dip switches Instance 				*/
XGpio PushInstance;			/* Push buttons Instance 				*/

/* Function pointer for the timer interrupt handler */
void (*TimerFunctionPtr)(void);

int main (void) 
{
	GpioInit(&DipInstance, XPAR_SWITCHES_DEVICE_ID);
	GpioInit(&PushInstance, XPAR_BUTTONS_DEVICE_ID);

	ScuTimerInit(&TimerInstance, XPAR_XSCUTIMER_0_DEVICE_ID, 100*MILLISECOND);
	ScuIntrInit(&IntcInstance, XPAR_SCUGIC_SINGLE_DEVICE_ID);
	TimerSetupIntr(&IntcInstance, &TimerInstance, XPAR_SCUTIMER_INTR);

	int input;

	xil_printf("\r\n-- Start of the Program --\r\n");

	while (1)
	{
		xil_printf("\r\nCMD:> ");
		input = inbyte();
		xil_printf("%c", input);
		switch (input)
		{
			case '0':
				xil_printf("\r\nNo action.");
				xil_printf("\r\nStopping Timer Routine.\n");
				TimerStop(&TimerInstance);
				TimerFunctionPtr = NULL;
				break;
			case '1':
				xil_printf("\r\nStarting Program 1.");
				xil_printf("\r\nSwitches to LEDs.\n");
				TimerReinitialize(&TimerInstance, 100*MILLISECOND, &read_switches);
				break;
			case '2':
				xil_printf("\r\nStarting Program 2.");
				xil_printf("\r\nLED Binary Counting.\n");
				TimerReinitialize(&TimerInstance, 1000*MILLISECOND, &count_leds);
				break;
			case '3':
				xil_printf("\r\nStarting Program 3.");
				xil_printf("\r\nSoft Matrix Multiplication.");
				TimerReinitialize(&TimerInstance, 1000*MILLISECOND, NULL);
				matrix_soft();
				break;
			case '4':
				xil_printf("\r\nStarting Program 4.");
				xil_printf("\r\nHard Matrix Multiplication.");
				TimerReinitialize(&TimerInstance, 1000*MILLISECOND, NULL);
				matrix_hard();
				break;
			default:
				xil_printf("\r\nUnrecognized input. \"%c\"\n", input);
				break;
		}
	}
}

void matrix_soft()
{
	vectorArray matrixA, matrixB, matrixP;
	volatile u32 start = 0;
	volatile u32 end = 0;

	setInputMatrices(matrixA, matrixB);

	xil_printf("\r\n\nMatrix A:\r\n");
	displayMatrix(matrixA);

	xil_printf("\r\n\nMatrix B:\r\n");
	displayMatrix(matrixB);

	start = XScuTimer_GetCounterValue(&TimerInstance);
	multiplyMatricesSoft(matrixA, matrixB, matrixP);
	end = XScuTimer_GetCounterValue(&TimerInstance);

	xil_printf("\r\n\nMatrix P (Result of multiplication):\r\n");
	displayMatrix(matrixP);

	/* Subtract 'end' from 'start' since XScuTimer is down counting */
	xil_printf("Clock cycles: %llu\n", 2 * (start - end));
}

void matrix_hard()
{
	vectorArray matrixA, matrixB, matrixP;
	volatile u32 start = 0;
	volatile u32 end = 0;

	setInputMatrices(matrixA, matrixB);

	xil_printf("\r\n\nMatrix A:\r\n");
	displayMatrix(matrixA);

	xil_printf("\r\n\nMatrix B:\r\n");
	displayMatrix(matrixB);

	start = XScuTimer_GetCounterValue(&TimerInstance);
	multiplyMatricesHard(matrixA, matrixB, matrixP);
	end = XScuTimer_GetCounterValue(&TimerInstance);

	xil_printf("\r\n\nMatrix P (Result of multiplication):\r\n");
	displayMatrix(matrixP);

	/* Subtract 'end' from 'start' since XScuTimer is down counting */
	xil_printf("Clock cycles: %llu\n", 2 * (start - end));
}

void read_switches()
{
	int switch_read = XGpio_DiscreteRead(&DipInstance, 1);
	LED_IP_mWriteReg(XPAR_LED_IP_S_AXI_BASEADDR, 0, switch_read);
}

void count_leds()
{
	static u8 count = 0;
	count = (count + 1) & 0x0F;
	LED_IP_mWriteReg(XPAR_LED_IP_S_AXI_BASEADDR, 0, count);
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
* Initializes the general interrupt controller.
*
* @param IntcInstancePtr is a pointer to the instance of XScuGic driver.
* @param GicDeviceId is the device Id of the XScuGic device.
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
******************************************************************************/
int ScuIntrInit(XScuGic *IntcInstancePtr, u16 GicDeviceId)
{
	XScuGic_Config *IntcConfig;
	int Status;

	IntcConfig = XScuGic_LookupConfig(GicDeviceId);
	if (NULL == IntcConfig) {
		xil_printf("Interrupt controller lookup failed.");
		return XST_FAILURE;
	}

	Status = XScuGic_CfgInitialize(IntcInstancePtr, IntcConfig, IntcConfig->CpuBaseAddress);
	if (Status != XST_SUCCESS) {
		xil_printf("Interrupt controller initialization failed.");
		return XST_FAILURE;
	}

	Xil_ExceptionInit();

	Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_IRQ_INT, (Xil_ExceptionHandler)XScuGic_InterruptHandler, IntcInstancePtr);

	return XST_SUCCESS;
}

/*****************************************************************************/
/**
* Connects the timer to the interrupt subsystem such that interrupts can occur.
*
* @param IntcInstancePtr is a pointer to the instance of XScuGic driver.
* @param TimerInstancePtr is a pointer to the instance of XScuTimer driver.
* @param TimerIntrId is the Interrupt Id of the XScuTimer device.
*
* @return	XST_SUCCESS if successful, otherwise XST_FAILURE.
******************************************************************************/
int TimerSetupIntr(XScuGic *IntcInstancePtr, XScuTimer *TimerInstancePtr, u16 TimerIntrId)
{
	int Status;

	Status = XScuGic_Connect(IntcInstancePtr, TimerIntrId, (Xil_ExceptionHandler)TimerIntrHandler, (void *)TimerInstancePtr);
	if (Status != XST_SUCCESS)
	{
		xil_printf("Timer interrupt connect failed.");
		return XST_FAILURE;
	}

	XScuGic_Enable(IntcInstancePtr, TimerIntrId);

	XScuTimer_EnableInterrupt(TimerInstancePtr);

	Xil_ExceptionEnable();

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

/*****************************************************************************/
/**
* Stops the timer.
*
* @param TimerInstancePtr is a pointer to the instance of XScuTimer driver.
* @return None
******************************************************************************/
void TimerStop(XScuTimer *TimerInstancePtr)
{
	XScuTimer_Stop(TimerInstancePtr);
}

/*****************************************************************************/
/**
* Loads the timer.
*
* @param TimerInstancePtr is a pointer to the instance of XScuTimer driver.
* @param TimerCounter is the value to load into the timer counter register.
* @return None
******************************************************************************/
void TimerLoad(XScuTimer *TimerInstancePtr, u32 TimerCounter)
{
	XScuTimer_LoadTimer(TimerInstancePtr, TimerCounter);
}

/*****************************************************************************/
/**
* Reinitializes the timer.
*
* @param TimerInstancePtr is a pointer to the instance of XScuTimer driver.
* @param TimerCounter is the value to load into the timer counter register.
* @param TimerFunction is the function pointer to the timer interrupt handler.
* @return None
******************************************************************************/
void TimerReinitialize(XScuTimer *TimerInstancePtr, u32 TimerCounter, void (*TimerFunction)(void))
{
	TimerStop(TimerInstancePtr);
	TimerFunctionPtr = TimerFunction;
	TimerLoad(TimerInstancePtr, TimerCounter);
	XScuTimer_RestartTimer(TimerInstancePtr);
	TimerStart(TimerInstancePtr);
}

/*****************************************************************************/
/**
* This function is the Interrupt handler for the Timer interrupt of the
* Timer device. It is called on the expiration of the timer counter in
* interrupt context.
*
* @param	CallBackRef is a pointer to the callback function.
*
* @return	None.
******************************************************************************/
static void TimerIntrHandler(void *CallBackRef)
{
	XScuTimer *TimerInstancePtr = (XScuTimer *) CallBackRef;
	XScuTimer_ClearInterruptStatus(TimerInstancePtr);

	if (TimerFunctionPtr != NULL) {
		TimerFunctionPtr();
	}
}

/*****************************************************************************/
/**
* This function disables the interrupts that occur for the device.
*
* @param IntcInstancePtr is the pointer to the instance of XScuGic driver.
* @param TimerIntrId is the Interrupt Id for the device.
*
* @return	None.
******************************************************************************/
static void TimerDisableIntrSystem(XScuGic *IntcInstancePtr, u16 TimerIntrId)
{
	XScuGic_Disconnect(IntcInstancePtr, TimerIntrId);
}

