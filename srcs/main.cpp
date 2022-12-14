#include	<iostream>
#include	"color.hpp"
#include	"Vector.hpp"

static void	test_vector(void)
{
	Vector<int>	vec;

	vec.assign(7, 100);
}

int	main(void)
{
	title("Main");

	test_vector();

	return 0;
}
