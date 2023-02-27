#include "stack.hpp"

template <typename T, typename _container_type>
bool
stack<T, _container_type>::empty(void) const
{
	return c.empty();
}

template <typename T, typename _container_type>
size_t
stack<T, _container_type>::size(void) const
{
	return c.size();
}

template <typename T, typename _container_type>
T &
stack<T, _container_type>::top(void) const
{
	return c.back();
}

template <typename T, typename _container_type>
void
stack<T, _container_type>::push(T const &value)
{
	c.push_back(value);
}

template <typename T, typename _container_type>
void
stack<T, _container_type>::pop(void)
{
	return c.pop_back();
}
