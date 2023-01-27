#ifndef STACK_HPP
#define STACK_HPP

#include "Vector.hpp"

namespace ft
{

template <typename T> class stack
{
  public:
	/* Member functions */
	void push(T const &);
	T	&top(void);

  private:
	vector<T> _container;
};

#include "../templates/Stack.cpp"

} /* namespace ft */

#endif /* STACK_HPP */
