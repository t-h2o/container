#include "SimpleString.hpp"
#include "color.hpp"

int
main(void)
{
	title("Simple string");

	SimpleString str("hello world");
	SimpleString str_empty;

	std::cout << str[0] << std::endl;

	return 0;
}
