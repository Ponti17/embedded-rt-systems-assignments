#include "systemc.h"
#include "cl.hpp"

/* Function Prototypes */
void cl_test(void);

int sc_main(int sc_argc, char* sc_argv[])
{
	cl_test();
	return 0;
}

void cl_test()
{
	/* Create command list instance */
    cl_type cl_instance;

    /* Create command list of size 16 */
	int size = 16;
    create_cl(cl_instance, size);

	/* Add values to array */
	for (int i = 0; i < cl_instance.size; ++i) {
		cl_instance.array[i] = i;
	}

    /* Loop through array */
    for (int i = 0; i < cl_instance.size; ++i) {
        std::cout << cl_instance.array[i] << " ";
    }
    std::cout << std::endl;

    /* Delete the cl_instance */
    delete_cl(cl_instance);
}

void error_handler(const char* message)
{
	std::cerr << message << std::endl;
	exit(1);
}