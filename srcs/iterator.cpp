#include "iterator.hpp"

ft::iterator::iterator(void) : _pointer(0), _position(0) {}

ft::iterator::iterator(char *ptr, size_t position)
	: _pointer(ptr), _position(position)
{
}

char &
ft::iterator::operator*(void) const
{
	return this->_pointer[0];
}

ft::iterator &
ft::iterator::operator++(void)
{
	this->_pointer++;
	return *this;
}

ft::iterator
ft::iterator::operator++(int)
{
	iterator prev(*this);
	this->_pointer++;
	return prev;
}

ft::iterator &
ft::iterator::operator--(void)
{
	this->_pointer--;
	return *this;
}

ft::iterator
ft::iterator::operator--(int)
{
	iterator prev(*this);
	this->_pointer--;
	return prev;
}
