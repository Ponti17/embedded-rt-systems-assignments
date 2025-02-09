/*
 * cl.hpp
 * Date Created: 09/11/24
*/

#ifndef CL_HPP
#define CL_HPP

/* Includes */
#include "systemc.h"

#define CMD_NONE        0x0000
#define BLIT_RECT_CMD   0x0001
#define BLIT_CIRC_CMD   0x0002
#define BLIT_LINE_CMD   0x0003

struct cl_type {
    sc_uint<32> idx  = 0;
    sc_uint<32> size = 0;
    sc_uint<32> *array = nullptr;
};

/**
 * Initialize the GPU
 * @param stride Stride
 * @param width Width
 * @param height Height
 * @return void
 */
void gpu_init(sc_uint<16> stride, sc_uint<16> width, sc_uint<16> height);

/**
 * Create a command list
 * @param cl Command list
 * @param size Size of the command list
 * @return void
 */
void create_cl(cl_type& cl, sc_uint<32> size);

/**
 * Delete a command list
 * @param cl Command list
 * @return void
 */
void delete_cl(cl_type& cl);

/**
 * Rewind a command list
 * @param cl Command list
 * @return void
 */
void rewind_cl(cl_type& cl);

/**
 * Bind a command list
 * @param cl Command list
 * @return void
 */
void bind_cl(cl_type& cl);

/**
 * Unbind a command list
 * @return void
 */
void unbind_cl();

/**
 * Get the currently bound command list
 * @return Command list
 */
cl_type& get_bound_cl();

/**
 * Construct a blit rectangle command.
 * Will be put in the currently bound command list.
 * @param x X coordinate
 * @param y Y coordinate
 * @param w Width
 * @param h Height
 * @param color Color (BGRA8888)
 * @return void
 */
void blit_rect(sc_uint<16> x, sc_uint<16> y, sc_uint<16> w, sc_uint<16> h, sc_uint<32> color);

/**
 * Construct a blit circ command.
 * Will be put in the currently bound command list.
 * @param x X coordinate
 * @param y Y coordinate
 * @param r Radius
 * @param color Color (BGRA8888)
 * @return void
 */
void blit_circ(sc_uint<16> x, sc_uint<16> y, sc_uint<16> r, sc_uint<32> color);

/**
 * Construct a blit line command.
 * Will be put in the currently bound command list.
 * @param x0 Start X coordinate
 * @param y0 Start Y coordinate
 * @param x1 End X coordinate
 * @param y1 End Y coordinate
 * @param t Thickness
 * @param color Color (BGRA8888)
 * @return void
 */
void blit_line(sc_uint<16> x0, sc_uint<16> y0, sc_uint<16> x1, sc_uint<16> y1, sc_uint<16> t, sc_uint<32> color);

#endif // CL_HPP
