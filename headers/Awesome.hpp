#ifndef	AWESOME_HPP
# define AWESOME_HPP

class	Awesome
{
	public:
		Awesome (int number = 0)
		{
			std::cout << number << " ";
			message("Awesome: default constructor");
			this->_number = new int(number);
		}
		~Awesome(void)
		{
			message("Awesome: destructor");
			delete this->_number;
			this->_number = 0;
		}
		Awesome(Awesome const &other) : _number(0)
		{
			std::cout << *(other._number) << " ";
			message("Awesome: copy constructor");
			*this = other;
		}

		Awesome	&operator=(Awesome const &other)
		{
			delete this->_number;
			message("Awesome: =");
			this->_number = new int(*(other._number));

			return *this;
		}

		int		get_number(void) const { return *(this->_number); }
		void	set_number(int number) { *(this->_number) = number; }

	private:
		int	*_number;
};

std::ostream	&operator<<(std::ostream &output, Awesome const &object)
{
	output << "Awesome : "
		<< object.get_number();

	return output;
}

#endif /* AWESOME_HPP */
