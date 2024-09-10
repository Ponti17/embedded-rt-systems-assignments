#ifndef DEFS_H
#define DEFS_H
//----------------------------------------------------------------------------------------------
// defs.h (systemc)
//
//							Danish Intsitute of Technology (Copyright)
//
//	Author: KBE / 2007.10.10
//----------------------------------------------------------------------------------------------
#define _TEST_SWEEP		1		// If defined test with sweep signal

#define CLK_PERIODE		30		// Clock periode in ns (33 Mhz, bus clock)
#define ALGO_BLOCK_SIZE	8		// Number of samples processed in one block
#define ALGO_BITS		16		// 16 bits resolution of samples 

#define WBUS			32		// Wide of processor bus interface

#define SAMPLE_FS		44100	// Sample rate in Hz
#define TEST_FC			1000    // Cut frequence for test of IIR filter

// User reg2 bits in algo block
#define CLEAR_PEAK_BIT  1		// Bit position to clear peak
#define ENABLE_IIR_BIT  2		// Bit position to enable IIR filter

// Functional level test
#define INPUT_FILE_F	"in_data_func.txt"		// Input data file (Floating point)
#define OUTPUT_FILE_F	"out_data_func.txt"     // Output data file functional level (Floating point)
#define OUTPUT_FILE_FF  "out_data_func_fix.txt" // Output data file functional level (Fixed point)

// Architecture level test
#define INPUT_FILE_A	"in_data_arch.txt"		// Input data file (Fixed point)
#define OUTPUT_FILE_A	"out_data_arch.txt"		// Output data file architechture level (Fixed point)

//------------------------------------------------------------------------------------------------

#if (ALGO_BITS == 16)
#define ALGO_SCALE		0x7fff    // 16 bit Maximum integer (15 bit + sign) value used for conversion float <-> fixed
#endif

#if (ALGO_BITS == 20)
#define ALGO_SCALE		0x7ffff   // 20 bit Maximum integer (19 bit + sign) value used for conversion float <-> fixed
#endif

#if (ALGO_BITS == 24)
#define ALGO_SCALE		0x7fffff  // 24 bit Maximum integer (23 bit + sign) value used for conversion float <-> fixed
#endif

#define float2fixed(i) ((int)(i*ALGO_SCALE))
#define fixed2float(i) ((float)i/ALGO_SCALE)

#endif
