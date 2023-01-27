#ifndef STACK_HPP
#define STACK_HPP

#include "Vector.hpp"

namespace ft
{

template <typename T> class stack
{
  public:
	/* Member functions */
	size_t size(void) const;
	T	  &top(void) const;
	void   push(T const &);

  private:
	vector<T> _container;
};

#include "../templates/Stack.cpp"

} /* namespace ft */

#endif /* STACK_HPP */
