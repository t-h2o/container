#ifndef AWESOME_HPP
#define AWESOME_HPP

#include <iostream>

#include "color.hpp"

class Awesome
{
  public:
	Awesome(int = 0);
	~Awesome(void);
	Awesome(Awesome const &other);

	Awesome &operator=(Awesome const &other);

	bool operator==(Awesome const &) const;

	int	 get_number(void) const;
	void set_number(int number);

  private:
	int *_number;
};

std::ostream &operator<<(std::ostream &output, Awesome const &object);

#endif /* AWESOME_HPP */
