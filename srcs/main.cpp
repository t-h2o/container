#include	<iostream>
#include	"color.hpp"
#include	"Vector.hpp"

static void	test_vector(void)
{
	Vector<int>	vec;

	section("assign 7 times the value 100");
	vec.assign(7, 100);

	section("print vec");
	std::cout << vec << std::endl;

	section("print the 3th number");
	std::cout << vec[3] << std::endl;
}

int	main(void)
{
	title("Main");

	test_vector();

	return 0;
}
