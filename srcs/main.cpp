#include	<iostream>
#include	"color.hpp"
#include	"Vector.hpp"
#include	<vector>

static void	test_my_vector(void)
{
	Vector<int>	vec;

	section("assign 7 times the value 100");
	vec.assign(7, 100);

	section("print vec");
	std::cout << vec << std::endl;

	section("add 1, 2, 3...");
	for (unsigned int i = 0; i < vec.size(); i++)
		vec[i] += i;

	section("print vec");
	std::cout << vec << std::endl;

	section("print the 3th number");
	std::cout << vec[3] << std::endl;

	section("print the front number");
	std::cout << vec.front() << std::endl;

	section("print the back number");
	std::cout << vec.back() << std::endl;
}

static void	test_vector(void)
{
	std::vector<int>	vec;

	section("assign 7 times the value 100");
	vec.assign(11, 100);

	section("print the 3th number");
	std::cout << vec[3] << std::endl;
}

int	main(void)
{
	title("Main");

	test_my_vector();
	test_vector();

	return 0;
}
