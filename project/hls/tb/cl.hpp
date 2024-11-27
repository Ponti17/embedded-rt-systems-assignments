/*
 * cl.hpp
 * Date Created: 09/11/24
*/

#ifndef CL_HPP
#define CL_HPP

/* Includes */
#include <ap_int.h>

#define CMD_NONE        0x0000
#define BLIT_RECT_CMD   0x0001
#define BLIT_CIRC_CMD   0x0002
#define BLIT_LINE_CMD   0x0003

struct cl_type {
    ap_uint<32> idx  = 0;
    ap_uint<32> size = 0;
    ap_uint<32> *array = nullptr;
};

/**
 * Initialize the GPU
 * @param stride Stride
 * @param width Width
 * @param height Height
 * @return void
 */
void gpu_init(ap_uint<16> stride, ap_uint<16> width, ap_uint<16> height);

/**
 * Create a command list
 * @param cl Command list
 * @param size Size of the command list
 * @return void
 */
void create_cl(cl_type& cl, ap_uint<32> size);

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
void blit_rect(ap_uint<16> x, ap_uint<16> y, ap_uint<16> w, ap_uint<16> h, ap_uint<32> color);

/**
 * Construct a blit circ command.
 * Will be put in the currently bound command list.
 * @param x X coordinate
 * @param y Y coordinate
 * @param r Radius
 * @param color Color (BGRA8888)
 * @return void
 */
void blit_circ(ap_uint<16> x, ap_uint<16> y, ap_uint<16> r, ap_uint<32> color);

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
void blit_line(ap_uint<16> x0, ap_uint<16> y0, ap_uint<16> x1, ap_uint<16> y1, ap_uint<16> t, ap_uint<32> color);

#endif // CL_HPP
