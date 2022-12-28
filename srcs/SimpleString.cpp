#include "SimpleString.hpp"

SimpleString::SimpleString(void) : _size(0), _str(0) {}

SimpleString::SimpleString(char const *str)
{
	_size = strlen(str) + 1;
	_str = new char[_size];

	strcpy(_str, str);
}

SimpleString::~SimpleString(void) { delete[] _str; }

char &
SimpleString::operator[](size_t position)
{
	return _str[position];
}

char &
SimpleString::operator[](size_t position) const
{
	return _str[position];
}

std::ostream &
operator<<(std::ostream &output, SimpleString const &object)
{
	for (size_t i = 0; object[i]; ++i)
		output << object[i];

	return output;
}
