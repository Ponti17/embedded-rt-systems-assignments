#include "Master.hpp"

template<class T>
Master<T>::Master(sc_module_name name) : sc_module(name)
{
	SC_THREAD(generateDataForAdapter);
}

template<class T>
void Master<T>::generateDataForAdapter()
{
}
