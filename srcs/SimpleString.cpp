#include "SimpleString.hpp"

ft::SimpleString::SimpleString(void) : _size(0), _str(0) {}

ft::SimpleString::SimpleString(char const *str)
{
	_size = strlen(str) + 1;
	_str = new char[_size];

	strcpy(_str, str);
}

ft::SimpleString::~SimpleString(void) { delete[] _str; }

SimpleStringIterator
ft::SimpleString::begin(void)
{
	return SimpleStringIterator(_str, 0);
}

TemplateIterator<char>
ft::SimpleString::end(void)
{
	return TemplateIterator<char>(_str, _size);
}

char &
ft::SimpleString::operator[](size_t position)
{
	return _str[position];
}

char &
ft::SimpleString::operator[](size_t position) const
{
	return _str[position];
}

std::ostream &
operator<<(std::ostream &output, ft::SimpleString const &object)
{
	for (size_t i = 0; object[i]; ++i)
		output << object[i];

	return output;
}
