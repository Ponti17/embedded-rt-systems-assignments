#include "xparameters.h"
#include "xgpio.h"
#include "led_ip.h"
#include "sleep.h"

//====================================================

void read_switches(XGpio dip);
unsigned int delay = 1; // seconds
int main (void) 
{
   XGpio dip, push;
	
   xil_printf("-- Start of the Program --\r\n");
 
   XGpio_Initialize(&dip, XPAR_SWITCHES_DEVICE_ID); // Modify this
   XGpio_SetDataDirection(&dip, 1, 0xffffffff);
	
   XGpio_Initialize(&push, XPAR_BUTTONS_DEVICE_ID); // Modify this
   XGpio_SetDataDirection(&push, 1, 0xffffffff);

   int value, skip;

   while (1)
   {
	  xil_printf("\r\nCMD:>");
	  value = inbyte();
	  skip = inbyte();
	  skip = inbyte();
	  switch (value)
	  {
	  	  case '1':
	  		  read_switches(dip);
	  		  xil_printf("\r\nReceived 1.");
	  	  case '2':
	  		  xil_printf("\r\nReceived 2.");
	  	  default:
	  		  xil_printf("\r\nUnrecognized input.");
	  }
   }
}

void read_switches (XGpio dip)
{
	int switch_read = XGpio_DiscreteRead(&dip, 1);
	LED_IP_mWriteReg(XPAR_LED_IP_S_AXI_BASEADDR, 0, switch_read);
}
