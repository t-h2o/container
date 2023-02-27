#include "stack.hpp"

template <typename T, typename _container_type>
bool
stack<T, _container_type>::empty(void) const
{
	return _container.empty();
}

template <typename T, typename _container_type>
size_t
stack<T, _container_type>::size(void) const
{
	return _container.size();
}

template <typename T, typename _container_type>
T &
stack<T, _container_type>::top(void) const
{
	return _container.back();
}

template <typename T, typename _container_type>
void
stack<T, _container_type>::push(T const &value)
{
	_container.push_back(value);
}

template <typename T, typename _container_type>
void
stack<T, _container_type>::pop(void)
{
	return _container.pop_back();
}
