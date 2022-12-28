#include "SimpleStringIterator.hpp"

SimpleStringIterator::SimpleStringIterator(char *ptr) : _pointer(ptr) {}

char &
SimpleStringIterator::operator*(void) const
{
	return this->_pointer[0];
}
