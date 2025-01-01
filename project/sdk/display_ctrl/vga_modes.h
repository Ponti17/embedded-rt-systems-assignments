/************************************************************************/
/*	@file vga_modes.h													*/
/*	@created 01/01/24													*/
/************************************************************************/

#ifndef VGA_MODES_H_
#define VGA_MODES_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	char label[64]; // Label describing the resolution
	u32 width; 		// Width of the active video frame
	u32 height; 	// Height of the active video frame
	u32 hps; 		// Start time of Horizontal sync pulse, in pixel clocks (active width + H. front porch)
	u32 hpe; 		// End time of Horizontal sync pulse, in pixel clocks (active width + H. front porch + H. sync width)
	u32 hmax; 		// Total number of pixel clocks per line (active width + H. front porch + H. sync width + H. back porch) 
	u32 hpol; 		// hsync pulse polarity
	u32 vps; 		// Start time of Vertical sync pulse, in lines (active height + V. front porch)
	u32 vpe; 		// End time of Vertical sync pulse, in lines (active height + V. front porch + V. sync width)
	u32 vmax; 		// Total number of lines per frame (active height + V. front porch + V. sync width + V. back porch) 
	u32 vpol; 		// vsync pulse polarity
	double freq; 	// Pixel Clock frequency
} VideoMode;

static const VideoMode VMODE_1920x1080 = {
	.label = "1920x1080@60Hz",
	.width = 1920,
	.height = 1080,
	.hps = 2008,
	.hpe = 2052,
	.hmax = 2199,
	.hpol = 1,
	.vps = 1084,
	.vpe = 1089,
	.vmax = 1124,
	.vpol = 1,
	.freq = 148.5 //148.57 is close enough
};

#ifdef __cplusplus
}
#endif

#endif /* VGA_MODES_H_ */
