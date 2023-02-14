#include "Awesome.hpp"
#include "Iterator.hpp"
#include "Tdd.hpp"
#include "color.hpp"
#include "vector.hpp"
#include <iostream>
#include <vector>

void
test_push_back(std::vector<int> &vec_std, ft::vector<int> &vec_ft, int number)
{
	vec_std.push_back(number);
	vec_ft.push_back(number);
}

void
test_vector_2(void)
{
	std::vector<int> vec_std;
	ft::vector<int>	 vec_ft;

	test_push_back(vec_std, vec_ft, 0);
	return;
}
