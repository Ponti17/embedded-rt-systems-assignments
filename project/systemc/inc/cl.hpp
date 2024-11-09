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

/**
 * Create a command list
 * @param cl Command list
 * @param size Size of the command list
 * @return void
 */
void create_cl(cl_type& cl, int size);

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

#endif // CL_HPP
