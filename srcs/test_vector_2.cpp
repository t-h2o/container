#include "Awesome.hpp"
#include "Iterator.hpp"
#include "Tdd.hpp"
#include "color.hpp"
#include "vector.hpp"
#include <iostream>
#include <vector>

template <typename TYPE>
static void
test_push_back(std::vector<TYPE> &vec_std, ft::vector<TYPE> &vec_ft, TYPE number)
{
	vec_std.push_back(number);
	vec_ft.push_back(number);
}

template <typename TYPE>
static void
start_test(void)
{
	std::vector<TYPE> vec_std;
	ft::vector<TYPE>  vec_ft;

	void (*f[2])(std::vector<TYPE> &, ft::vector<TYPE> &, TYPE);
	f[0] = &test_push_back<TYPE>;
	f[0](vec_std, vec_ft, 0);
}

void
test_vector_2(void)
{
	title("test vector 2.0");

	start_test<int>();
	start_test<Awesome>();

	return;
}
