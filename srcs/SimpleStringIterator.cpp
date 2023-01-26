#include "SimpleStringIterator.hpp"

ft::SimpleStringIterator::SimpleStringIterator(void)
	: _pointer(0), _position(0)
{
}

ft::SimpleStringIterator::SimpleStringIterator(char *ptr, size_t position)
	: _pointer(ptr), _position(position)
{
}

char &
ft::SimpleStringIterator::operator*(void) const
{
	return this->_pointer[0];
}

ft::SimpleStringIterator &
ft::SimpleStringIterator::operator++(void)
{
	this->_pointer++;
	return *this;
}

ft::SimpleStringIterator
ft::SimpleStringIterator::operator++(int)
{
	SimpleStringIterator prev(*this);
	this->_pointer++;
	return prev;
}

ft::SimpleStringIterator &
ft::SimpleStringIterator::operator--(void)
{
	this->_pointer--;
	return *this;
}

ft::SimpleStringIterator
ft::SimpleStringIterator::operator--(int)
{
	SimpleStringIterator prev(*this);
	this->_pointer--;
	return prev;
}
