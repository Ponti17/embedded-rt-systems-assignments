#ifndef TOP_H_
#define TOP_H_
//============================================================================
// Name        : Top.cpp
// Author      : Kim Bjerge
// Version     : 22. feb 2008
// Copyright   : Danish Technological Institute
// Description : Example of a parameterized design using templates
//               Contains the top level design 
//				 at functional and architecture level
//============================================================================

#define SC_INCLUDE_FX
#include <systemc.h>
#include "Defs.h"
#include "ParFir.h"
#include "Source.h"
#include "Monitor.h"
#include "Mixer.h"
#include "Fork.h"

//#define SC_ARCHITECTURE //Must be set for the ModelSim simulation 

//#define _HIGH_PASS // Default creates a LOW PASS filter

// Configurations parameters for the FIR filter model
const unsigned fs = 44100; 		// Sample frequence
const unsigned fc = 2000;  		// Cut frequence for filter
const int samples = 1000; 		// Number of samples 
const unsigned taps = TABS;		// Size of filter

// Name of monitor files
const std::string rtl_file("output_rtl.txt");
const std::string mix_file("mix_file.txt");

#ifdef SC_ARCHITECTURE
typedef sc_fixed<18,2> fir_T;
const std::string ref_file("output_fixed.txt");
#else	
typedef double fir_T;
const std::string ref_file("output_double.txt");
#endif

class Top : public sc_module
{
public:

	// Create fifo channels
	sc_fifo<fir_T> input_1k;
	sc_fifo<fir_T> input_2k;
	sc_fifo<fir_T> input_3k;
	sc_fifo<fir_T> mix_out;
	sc_fifo<fir_T> fir_in;
	sc_fifo<fir_T> monitor_in;
	sc_fifo<fir_T> output;
	
	// Signal generator 1 kHz sine
	Source<fir_T> src_sine_1k;

	// Signal generator 2 kHz sine
	Source<fir_T> src_sine_2k;

	// Signal generator 3 kHz sine
	Source<fir_T> src_sine_3k; 
	
	// Mixer to add the sine signals together
	Mixer<fir_T> mix;

	// Split the mixed signal in 2 
	Fork<fir_T> fork;
	
	// Monitor of mixed input result
	Monitor<fir_T,1> monitor_mix;

	HighPassFir<double, taps> *pHighPass; // HighPass filter coefficients
	LowPassFir<double, taps> *pLowPass; // LowPass filter coefficients
	ParFir<fir_T, taps> *pFir; // Fir filter
		
	// Monitor of filtered output result
	Monitor<fir_T,6> monitor_ref;

	// Architecture model of Fir filter

	SC_HAS_PROCESS(Top);
	Top(sc_module_name name);
};

#endif /*TOP_H_*/

