#include "SimpleString.hpp"

SimpleString::SimpleString(void) : _size(0), _str(0) {}

SimpleString::SimpleString(char const *str)
{
	_size = strlen(str) + 1;
	_str = new char[_size];

	strcpy(_str, str);
}

SimpleString::~SimpleString(void) { delete[] _str; }
