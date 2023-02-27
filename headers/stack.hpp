#ifndef STACK_HPP
#define STACK_HPP

#include "vector.hpp"

namespace ft
{

template <typename T, typename _container_type = ft::vector<T> > class stack
{
  public:
	typedef _container_type container_type;
	typedef typename container_type::iterator iterator;
	/* Member functions */
	bool   empty(void) const;
	size_t size(void) const;
	T	  &top(void) const;
	void   push(T const &);
	void   pop(void);

  private:
	container_type _container;
};

#include "../templates/stack.cpp"

} /* namespace ft */

#endif /* STACK_HPP */
