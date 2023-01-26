#ifndef SIMPLE_STRING_ITERATOR_HPP
#define SIMPLE_STRING_ITERATOR_HPP

#include <iostream>

namespace ft
{

class SimpleStringIterator
{
  public:
	SimpleStringIterator(void);
	SimpleStringIterator(char *, size_t);

	char &operator*(void) const;

	SimpleStringIterator &operator++(void);
	SimpleStringIterator  operator++(int);

	SimpleStringIterator &operator--(void);
	SimpleStringIterator  operator--(int);

  private:
	char  *_pointer;
	size_t _position;
};

} /* namespace: ft */

#endif /* SIMPLE_STRING_ITERATOR_HPP */
