/************************************************************************/
/*																		*/
/*	gfxlib.c	--	Low-Level Graphics Library 						    */
/*      Utilizes ARM core i.e. NO hardware acceleration                 */
/*																		*/
/************************************************************************/
/* Authors:                                                             */
/*      Andreas Pedersen    										    */
/*      Alexandre Cherencq                                              */
/************************************************************************/
/*  Date Created:   													*/
/*		20/10/2024(AP)	        										*/
/************************************************************************/

#include "main.h"
#include "display_ctrl.h"
#include "gfxlib.h"

void gfx_init(DisplayCtrl *dispCtrl)
{
    // Initialize the graphics library
    // This function is not implemented yet
}

void swap_buffer()
{
    // Swap the two frame buffers
    // This function is not implemented yet
}

/**
 * Blit a rectangle of color at position x, y with width w and height h
 * @param frame pointer to the frame buffer
 * @param x x-coordinate of the top-left corner of the rectangle
 * @param y y-coordinate of the top-left corner of the rectangle
 * @param w width of the rectangle
 * @param h height of the rectangle
 * @param color color of the rectangle (BGRA8888)
 * @return void
 */
void blit_rect(u8 *frame, u32 x, u32 y, u16 w, u16 h, u32 color)
{
	int xPix, yPix;
	for (xPix = 0; xPix < RESX; xPix++)
	{
		for (y = 0; y < RESY; y++)
		{
			if (xPix > x && xPix < x + w && yPix > y && y < y + h)
			{
				frame[y * RESY * 4 + x * 4] 	= color & 0xFF000000; // B
				frame[y * RESY * 4 + x * 4 + 1] = color & 0x00FF0000; // G
				frame[y * RESY * 4 + x * 4 + 2] = color & 0x0000FF00; // R
				frame[y * RESY * 4 + x * 4 + 3] = color & 0x000000FF; // A
			}
		}
	}
}

void blit_circ(uint32_t x, uint32_t y, uint32_t r, uint32_t color)
{
    // Blit a circle of color at position x, y with radius r
    // This function is not implemented yet
}

/**
 * Flushes the data cache for the frame buffer
 * @param frame pointer to the frame buffer
 * @return void
 */
void flush_fb(u8 *frame)
{
	Xil_DCacheFlushRange((unsigned int) frame, FB_SIZE);
}