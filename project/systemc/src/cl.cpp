/*
 * cl.cpp
 * Date Created: 09/11/24
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