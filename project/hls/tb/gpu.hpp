/*
 * gpu.hpp
 * Date Created: 09/11/24
*/

#ifndef GPU_HPP
#define GPU_HPP

#include "systemc.h"
#include <iostream>
#include <string>
#include "cl.hpp"
#include "fb.hpp"
#include <ap_int.h>

void submit_cl();
void bind_fb(fb_type* fb);

#endif // GPU_HPP
