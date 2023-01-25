#ifndef SIMPLE_STRING_HPP
#define SIMPLE_STRING_HPP

#include <iostream>
#include <string.h>

#include "SimpleStringIterator.hpp"
#include "TemplateIterator.hpp"

namespace ft
{

class string
{
  public:
	string(void);
	string(char const *);
	~string(void);

	SimpleStringIterator   begin(void);
	TemplateIterator<char> end(void);

	char &operator[](size_t);
	char &operator[](size_t) const;

  private:
	size_t _size;
	char  *_str;
};

} /* namespace: ft */

std::ostream &operator<<(std::ostream &output, ft::string const &object);

#endif /* SIMPLE_STRING_HPP */
