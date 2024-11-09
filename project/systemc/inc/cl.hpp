/*
 * cl.hpp
 * Date Created: 09/11/24
*/

#ifndef CL_HPP
#define CL_HPP

struct cl_type {
    int idx  = 0;
    int size = 0;
    int *array = nullptr;
};

void create_cl(cl_type& cl, int size);
void delete_cl(cl_type& cl);

#endif // CL_HPP
