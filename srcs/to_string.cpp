#include "to_string.hpp"

namespace ft
{

std::string
to_string(int __val)
{
	std::stringstream ss;
	ss << __val;
	std::string s = ss.str();
	return s;
}

}
