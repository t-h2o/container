#include "Awesome.hpp"
#include "Iterator.hpp"
#include "Tdd.hpp"
#include "color.hpp"
#include "vector.hpp"
#include <iostream>
#include <vector>

#include <stdlib.h> /* rand(), srand() */

#include "test_vector_2_compare.cpp"

#define TEST_NUMBER 2

template <typename TYPE>
static void
test_push_back(std::vector<TYPE> &vec_std, ft::vector<TYPE> &vec_ft, int random)
{
	section("push_back()");
	vec_std.push_back(random);
	vec_ft.push_back(random);
}

template <typename TYPE>
static void
test_pop_back(std::vector<TYPE> &vec_std, ft::vector<TYPE> &vec_ft, int random)
{
	section("pop_back()");
	(void)random;
	vec_std.pop_back();
	vec_ft.pop_back();
}

template <typename TYPE>
static void
start_test(int seed)
{
	srand(seed);
	std::vector<TYPE> vec_std;
	ft::vector<TYPE>  vec_ft;

	void (*f[TEST_NUMBER])(std::vector<TYPE> &, ft::vector<TYPE> &, int);

	f[0] = &test_push_back<TYPE>;
	f[1] = &test_pop_back<TYPE>;

	compare_vector(vec_std, vec_ft);

	for (int i = 0; i < 10; ++i)
	{
		f[rand() % TEST_NUMBER](vec_std, vec_ft, rand());

		compare_vector(vec_std, vec_ft);
	}
}

void
test_vector_2(void)
{
	title("test vector 2.0");

	for (int i = 0; i < 10; ++i)
	{
		section("new test");
		start_test<int>(i);
		start_test<Awesome>(i);
	}

	return;
}
