#include "Stack.hpp"

template <typename T>
void
stack<T>::push(T const &value)
{
	std::cout << value << std::endl;
	_container.push_back(value);
}

template <typename T>
T &
stack<T>::top(void)
{
	return _container.back();
}
