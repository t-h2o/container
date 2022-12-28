#include "SimpleString.hpp"
#include "color.hpp"

int
main(void)
{
	SimpleStringIterator it;

	title("Simple string");

	SimpleString str("hello world");
	SimpleString str_empty;

	std::cout << str << std::endl;

	it = str.begin();

	std::cout << *(it) << std::endl;
	std::cout << *(it++) << std::endl;
	std::cout << *(it) << std::endl;

	std::cout << *(it) << std::endl;
	std::cout << *(++it) << std::endl;
	std::cout << *(it) << std::endl << std::endl;

	std::cout << *(it) << std::endl;
	std::cout << *(it--) << std::endl;
	std::cout << *(it) << std::endl;

	std::cout << *(it) << std::endl;
	std::cout << *(--it) << std::endl;
	std::cout << *(it) << std::endl;

	return 0;
}
