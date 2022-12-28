#include "SimpleStringIterator.hpp"

SimpleStringIterator::SimpleStringIterator(void) : _pointer(0), _position(0) {}

SimpleStringIterator::SimpleStringIterator(char *ptr, size_t position)
	: _pointer(ptr), _position(position)
{
}

char &
SimpleStringIterator::operator*(void) const
{
	return this->_pointer[0];
}

SimpleStringIterator &
SimpleStringIterator::operator++(void)
{
	this->_pointer++;
	return *this;
}

SimpleStringIterator
SimpleStringIterator::operator++(int)
{
	SimpleStringIterator prev(*this);
	this->_pointer++;
	return prev;
}

SimpleStringIterator &
SimpleStringIterator::operator--(void)
{
	this->_pointer--;
	return *this;
}

SimpleStringIterator
SimpleStringIterator::operator--(int)
{
	SimpleStringIterator prev(*this);
	this->_pointer--;
	return prev;
}
