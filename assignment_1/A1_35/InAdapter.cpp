#include "InAdapter.hpp"

template<class T>
inline InAdapter<T>::InAdapter(sc_module_name name)
{

}
template<class T>
void InAdapter<T>::write(const T& data)
{
}

template <class T>
bool InAdapter<T>::nb_write(const T& data)
{
}

template <class T>
int InAdapter<T>::num_free() const
{
}

template <class T>
const sc_event& InAdapter<T>::data_read_event() const
{
}
