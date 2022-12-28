#include "SimpleString.hpp"
#include "color.hpp"

int
main(void)
{
	title("Simple string");

	SimpleString str("hello world");
	SimpleString str_empty;

	std::cout << str[0] << std::endl;
	std::cout << str << std::endl;

	SimpleStringIterator it = str.begin();

	(void)it;

	return 0;
}
