/*
 * cl.cpp
 * Date Created: 09/11/24
 * 
 * DESCRIPTION:
 * This file contains the implementation for the command list API.
 * 
 * A command list uses the same concept as the CPU stack, but lists GPU commands
 * to be executed. The command list is a simple array of 32-bit values.
 * 
 * The cl object is allocated in memory and "bound". When the cl object is bound,
 * the GPU stores the address of the cl object and can read the commands from it.
 * 
 * New commands can be added to a bound cl object.
 * 
 * In the final implementation the construction and binding of command lists
 * will be handled by the CPU.
*/

#include "cl.hpp"

/* External function prototypes */
void error_handler(const char* message);

/* Private function prototypes */
void init_check();
void cl_bound_check();
void set_cl_entry_split(sc_uint<16> msb, sc_uint<16> lsb);
void set_cl_entry_full(sc_uint<32> value);

/* Static variables */
static cl_type* bound_cl = nullptr;
static sc_uint<16> STRIDE   = 0;
static sc_uint<16> RESX     = 0;
static sc_uint<16> RESY     = 0;
static bool INIT = false;

void gpu_init(sc_uint<16> stride, sc_uint<16> width, sc_uint<16> height)
{
    STRIDE = stride;
    RESX   = width;
    RESY   = height;
    INIT   = true;
}

void init_check()
{
    if (INIT) {
        return;
    }

    error_handler("GPU not initialized");
}

void cl_bound_check()
{
    if (bound_cl != nullptr) {
        return; 
    }

    error_handler("No command list bound");
}

void create_cl(cl_type& cl, sc_uint<32> size)
{
    init_check();

    cl.array = new sc_uint<32>[size]();
    cl.size  = size;
    cl.idx   = 0;
}

void delete_cl(cl_type& cl)
{
    init_check();

    delete[] cl.array;
    cl.array = nullptr;
    cl.size = 0;
    cl.idx = 0;
}

void rewind_cl(cl_type& cl)
{
    init_check();
    cl_bound_check();

    cl.idx = 0;
}

void bind_cl(cl_type& cl)
{
    init_check();

    bound_cl = &cl;
}

void unbind_cl()
{
    init_check();
    cl_bound_check();

    bound_cl = nullptr;
}

cl_type& get_bound_cl() {
    return *bound_cl;
}

/**
 * Construct a blit rectangle command.
 * Will be put in the currently bound command list.
 * Byte 0: [31:16] = x, [15:0] = Command
 * Byte 1: [31:16] = w, [15:0] = y
 * Byte 2: [31:16] = 0, [15:0] = h
 * Byte 3: [31:0] = color
 */
void blit_rect(sc_uint<16> x, sc_uint<16> y, sc_uint<16> w, sc_uint<16> h, sc_uint<32> color)
{
    init_check();
    cl_bound_check();

    set_cl_entry_split(x, BLIT_RECT_CMD);
    set_cl_entry_split(w, y);
    set_cl_entry_split(0, h);
    set_cl_entry_full(color);
}

/**
 * Construct a blit circle command.
 * Will be put in the currently bound command list.
 * Byte 0: [31:16] = x, [15:0] = Command
 * Byte 1: [31:16] = r, [15:0] = y
 * Byte 2: [31:0] = color
 */
void blit_circ(sc_uint<16> x, sc_uint<16> y, sc_uint<16> r, sc_uint<32> color)
{
    init_check();
    cl_bound_check();

    set_cl_entry_split(x, BLIT_CIRC_CMD);
    set_cl_entry_split(r, y);
    set_cl_entry_full(color);
}

/**
 * Construct a blit line command.
 * Will be put in the currently bound command list.
 * Byte 0: [31:16] = x1, [15:0] = Command
 * Byte 1: [31:16] = x2, [15:0] = y1
 * Byte 2: [31:16] = t, [15:0] = y2
 * Byte 2: [31:0] = color
 */
void blit_line(sc_uint<16> x0, sc_uint<16> y0, sc_uint<16> x1, sc_uint<16> y1, sc_uint<16> t, sc_uint<32> color)
{
    init_check();
    cl_bound_check();

    set_cl_entry_split(x0, BLIT_LINE_CMD);
    set_cl_entry_split(x1, y0);
    set_cl_entry_split(t, y1);
    set_cl_entry_full(color);
}

/**
 * Sets a 32 bit value in the command list and increments the index.
 */
void set_cl_entry_split(sc_uint<16> msb, sc_uint<16> lsb)
{
    init_check();
    cl_bound_check();

    bound_cl->array[bound_cl->idx] = (static_cast<uint32_t>(msb) << 16) | (static_cast<uint32_t>(lsb));
    bound_cl->idx++;
}

/**
 * Sets a full 32-bit value in the command list and increments the index.
 */
void set_cl_entry_full(sc_uint<32> value)
{
    init_check();
    cl_bound_check();

    // Directly set the 32-bit value
    bound_cl->array[bound_cl->idx] = static_cast<uint32_t>(value);
    bound_cl->idx++;
}