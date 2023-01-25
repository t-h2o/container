#include "string.hpp"

ft::string::string(void) : _size(0), _str(0) {}

ft::string::string(char const *str)
{
	_size = strlen(str) + 1;
	_str = new char[_size];

	strcpy(_str, str);
}

ft::string::~string(void) { delete[] _str; }

SimpleStringIterator
ft::string::begin(void)
{
	return SimpleStringIterator(_str, 0);
}

TemplateIterator<char>
ft::string::end(void)
{
	return TemplateIterator<char>(_str, _size);
}

char &
ft::string::operator[](size_t position)
{
	return _str[position];
}

char &
ft::string::operator[](size_t position) const
{
	return _str[position];
}

std::ostream &
operator<<(std::ostream &output, ft::string const &object)
{
	for (size_t i = 0; object[i]; ++i)
		output << object[i];

	return output;
}
