#include "xparameters.h"
#include "xgpio.h"
#include "led_ip.h"
#include "sleep.h"
#include "xscutimer.h"
#include "xscugic.h"

//====================================================

void read_switches(XGpio dip);
int configure_timer(XScuTimer timer);
unsigned long delay = 100000; // useconds
#define ONE_SECOND 325000000

XScuTimer Timer;
XScuGic IntcInstance;

int main (void) 
{
	configure_timer(Timer);

	XGpio dip, push;
 
	XGpio_Initialize(&dip, XPAR_SWITCHES_DEVICE_ID);
	XGpio_SetDataDirection(&dip, 1, 0xffffffff);
	
	XGpio_Initialize(&push, XPAR_BUTTONS_DEVICE_ID);
	XGpio_SetDataDirection(&push, 1, 0xffffffff);

	int value, skip;

	xil_printf("-- Start of the Program --\r\n");

	while (1)
	{
	  xil_printf("\r\nCMD:> ");
	  value = inbyte();
	  xil_printf("%c", value);
	  skip = inbyte();
	  skip = inbyte();
	  switch (value)
	  {
	  	  case '1':
	  		  xil_printf("SW->Leds");
	  		  read_switches(dip);
	  		  break;
	  	  case '2':
	  		  xil_printf("\r\nReceived 2.");
	  		  break;
	  	  default:
	  		  xil_printf("\r\nUnrecognized input.");
	  		  break;
	  }
	  usleep(delay);
	}
}

int configure_timer(XScuTimer timer)
{
	XScuTimer_Config *ConfigPtr;
	XScuTimer *TimerInstancePtr = &timer;
	int Status;

	ConfigPtr = XScuTimer_LookupConfig(XPAR_PS7_SCUTIMER_0_DEVICE_ID);
	Status = XScuTimer_CfgInitialize(TimerInstancePtr, ConfigPtr, ConfigPtr->BaseAddr);
	if (Status != XST_SUCCESS) {
		xil_printf("Timit init() failed\r\n");
		return XST_FAILURE;
	}

	XScuTimer_LoadTimer(TimerInstancePtr, ONE_SECOND);
	XScuTimer_EnableAutoReload(TimerInstancePtr);
	XScuTimer_Start(TimerInstancePtr);
	if (XScuTimer_IsExpired(TimerInstancePtr)) {
		XScuTimer_ClearInterruptStatus(TimerInstancePtr);
	}
	return Status;
}

void read_switches (XGpio dip)
{
	int switch_read = XGpio_DiscreteRead(&dip, 1);
	LED_IP_mWriteReg(XPAR_LED_IP_S_AXI_BASEADDR, 0, switch_read);
}

void count_leds (XGpio dip)
{
	xil_printf("Test");
}
