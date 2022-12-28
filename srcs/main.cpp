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
	std::cout << *(it) << std::endl << std::endl;

	TemplateIterator<char> paul;

	paul = str.end();
	paul--;
	paul--;

	std::cout << *(paul) << std::endl;
	std::cout << *(paul--) << std::endl;
	std::cout << *(paul) << std::endl;

	std::cout << *(paul) << std::endl;
	std::cout << *(--paul) << std::endl;
	std::cout << *(paul) << std::endl;

	return 0;
}
