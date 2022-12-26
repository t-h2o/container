#include	"Awesome.hpp"

Awesome::Awesome (int number)
{
	std::cout << number << " ";
	message("Awesome: default constructor");
	this->_number = new int(number);
}
Awesome::~Awesome(void)
{
	message("Awesome: destructor");
	delete this->_number;
	this->_number = 0;
}
Awesome::Awesome(Awesome const &other) : _number(0)
{
	std::cout << *(other._number) << " ";
	message("Awesome: copy constructor");
	*this = other;
}

Awesome & Awesome::operator=(Awesome const &other)
{
	delete this->_number;
	message("Awesome: =");
	this->_number = new int(*(other._number));

	return *this;
}

int		Awesome::get_number(void) const { return *(this->_number); }
void	Awesome::set_number(int number) { *(this->_number) = number; }

std::ostream	&operator<<(std::ostream &output, Awesome const &object)
{
	output << "Awesome : "
		<< object.get_number();

	return output;
}
