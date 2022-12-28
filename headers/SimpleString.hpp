#ifndef SIMPLE_STRING_HPP
#define SIMPLE_STRING_HPP

#include <iostream>
#include <string.h>

class SimpleString
{
  public:
	SimpleString(void);
	SimpleString(char const *);
	~SimpleString(void);

	char &operator[](size_t);
	char &operator[](size_t) const;

  private:
	size_t _size;
	char  *_str;
};

std::ostream &operator<<(std::ostream &output, SimpleString const &object);

#endif /* SIMPLE_STRING_HPP */
