/************************************************************************/
/*	@file cl.h        												    */
/*	@created 30/12/24													*/
/************************************************************************/

#ifndef DISPLAY_DEMO_H_
#define DISPLAY_DEMO_H_

#ifdef __cplusplus
extern "C" {
#endif

/* ------------------------------------------------------------ */
/*				Include File Definitions						*/
/* ------------------------------------------------------------ */

#include "xil_types.h"

/* ------------------------------------------------------------ */
/*					Miscellaneous Declarations					*/
/* ------------------------------------------------------------ */

#define DEMO_PATTERN_0 0
#define DEMO_PATTERN_1 1

#define DEMO_MAX_FRAME (1920*1080*4)
#define DEMO_STRIDE (1920 * 4)

/* ------------------------------------------------------------ */
/*					Procedure Declarations						*/
/* ------------------------------------------------------------ */

int main(void);
void InitGPU();
void GPU_BindFrameBuffer(u32 frameBufferAddr);
void GPU_BindCommandList(u32 commandListAddr);
void GPU_Start();
void GPU_WaitForDone();
void Error_Handler();
void PrintStartup();

#ifdef __cplusplus
}
#endif

#endif /* DISPLAY_DEMO_H_ */
