/************************************************************************/
/*                                                                      */
/*	main.h    --	Application Main                                    */
/*                                                                      */
/************************************************************************/
/* Authors:                                                             */
/*      Andreas Pedersen                                                */
/*      Alexandre Cherencq                                              */
/************************************************************************/
/*  Date Created:                                                       */
/*		22/10/2024(AP)                                                  */
/************************************************************************/

#ifndef MAIN_H
#define MAIN_H

/* ------------------------------------------------------------ */
/*				Include File Definitions						*/
/* ------------------------------------------------------------ */

#include "xil_types.h"

/* ------------------------------------------------------------ */
/*					Miscellaneous Declarations					*/
/* ------------------------------------------------------------ */

#define DEMO_PATTERN_0 0
#define DEMO_PATTERN_1 1

#define FB_SIZE (1920 * 1080 * 4)
#define STRIDE (1920 * 4)

/* ------------------------------------------------------------ */
/*					Procedure Declarations						*/
/* ------------------------------------------------------------ */

void DemoInitialize();
void DemoRun();
void DemoPrintMenu();
void DemoChangeRes();
void DemoCRMenu();
void DemoInvertFrame(u8 *srcFrame, u8 *destFrame, u32 width, u32 height, u32 stride);
void DemoPrintTest(u8 *frame, u32 width, u32 height, u32 stride, int pattern);

/* ------------------------------------------------------------ */

/************************************************************************/

#endif /* MAIN_H */
