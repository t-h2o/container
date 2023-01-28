#include "Stack.hpp"

template <typename t>
bool
stack<t>::empty(void) const
{
	return _container.empty();
}

template <typename t>
size_t
stack<t>::size(void) const
{
	return _container.size();
}

template <typename T>
T &
stack<T>::top(void) const
{
	return _container.back();
}

template <typename t>
void
stack<t>::push(t const &value)
{
	_container.push_back(value);
}

template <typename T>
void
stack<T>::pop(void)
{
	return _container.pop_back();
}

template <typename T>
void
stack<T>::swap(stack<T> &other)
{
	return _container.swap(other._container);
}
