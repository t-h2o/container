#include "color.hpp"
#include "string.hpp"

int
main(void)
{
	ft::SimpleStringIterator it;

	title("Simple string");

	ft::string str("hello world");
	ft::string str_empty;

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
