#include	"Vector.hpp"

Vector::Vector(void)
{
	message("Vector: default constructor");
	this->_list = new int[0];
}

Vector::~Vector(void)
{
	message("Vector: destructor");

	delete [] this->_list;
}

void	Vector::assign(unsigned int nElements, int value)
{
	message("Vector: assign");

	delete [] this->_list;

	this->_list = new int[nElements];

	for (unsigned int i = 0; i < nElements; i++)
		this->_list[i] = value;
}
