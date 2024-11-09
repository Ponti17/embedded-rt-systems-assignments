/*
 * cl.cpp
 * Date Created: 09/11/24
*/

#include "cl.hpp"

/* External function prototypes */
void error_handler(const char* message);

/* Static variables */
static cl_type* bound_cl = nullptr;

void create_cl(cl_type& cl, int size)
{
    cl.array = new int[size]();
    cl.size  = size;
    cl.idx   = 0;
}

void delete_cl(cl_type& cl)
{
    delete[] cl.array;
    cl.array = nullptr;
    cl.size = 0;
    cl.idx = 0;
}

void rewind_cl(cl_type& cl)
{
    cl.idx = 0;
}

void bind_cl(cl_type& cl)
{
    bound_cl = &cl;
}

void unbind_cl()
{
    bound_cl = nullptr;
}

void blit_rect(cl_type& cl, int x, int y, int w, int h)
{
    if (bound_cl == nullptr)
    {
        error_handler("No command list bound");
    }

    if (cl.idx + 4 > cl.size)
    {
        return;
    }

    cl.array[cl.idx++] = x;
    cl.array[cl.idx++] = y;
    cl.array[cl.idx++] = w;
    cl.array[cl.idx++] = h;
}