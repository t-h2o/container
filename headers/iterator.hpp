#ifndef SIMPLE_STRING_ITERATOR_HPP
#define SIMPLE_STRING_ITERATOR_HPP

#include <iostream>

namespace ft
{

class iterator
{
  public:
	iterator(void);
	iterator(char *, size_t);

	char &operator*(void) const;

	iterator &operator++(void);
	iterator  operator++(int);

	iterator &operator--(void);
	iterator  operator--(int);

  private:
	char  *_pointer;
	size_t _position;
};

} /* namespace: ft */

#endif /* SIMPLE_STRING_ITERATOR_HPP */
