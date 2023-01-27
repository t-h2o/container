#ifndef STACK_HPP
#define STACK_HPP

#include "Vector.hpp"

namespace ft
{

template <typename T> class stack : public vector<T>
{
  public:
	void push(T const &);
};

#include "../templates/Stack.cpp"

} /* namespace ft */

#endif /* STACK_HPP */
