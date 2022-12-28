#ifndef SIMPLE_STRING_ITERATOR_HPP
#define SIMPLE_STRING_ITERATOR_HPP

#include <iostream>

class SimpleStringIterator
{
  public:
	SimpleStringIterator(char *, size_t);

	char &operator*(void) const;

	SimpleStringIterator &operator++(void);
	SimpleStringIterator  operator++(int);

  private:
	char  *_pointer;
	size_t _position;
};

#endif /* SIMPLE_STRING_ITERATOR_HPP */
