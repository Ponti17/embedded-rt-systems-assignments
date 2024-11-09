/*
 * cl.cpp
 * Date Created: 09/11/24
*/

#include "cl.hpp"

void create_cl(cl_type& cl, int size) {
    cl.array = new int[size]();
    cl.size  = size;
    cl.idx   = 0;
}

void delete_cl(cl_type& cl) {
    delete[] cl.array;
    cl.array = nullptr;
    cl.size = 0;
    cl.idx = 0;
}