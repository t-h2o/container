#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{

template <typename T> class stack
{
  public:
	/* Member functions */
	bool   empty(void) const;
	size_t size(void) const;
	T	  &top(void) const;
	void   push(T const &);
	void   pop(void);

  private:
	vector<T> _container;
};

#include "../templates/stack.cpp"

} /* namespace ft */

#endif /* STACK_HPP */
