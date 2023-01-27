#include "Stack.hpp"

template <typename t>
size_t
stack<t>::size(void) const
{
	return _container.size();
}

template <typename t>
void
stack<t>::push(t const &value)
{
	_container.push_back(value);
}

template <typename T>
T &
stack<T>::top(void) const
{
	return _container.back();
}
