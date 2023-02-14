#include "Awesome.hpp"
#include "Iterator.hpp"
#include "Tdd.hpp"
#include "color.hpp"
#include "vector.hpp"
#include <iostream>
#include <vector>

#include <stdlib.h> /* rand(), srand() */

#include "test_vector_2_compare.cpp"

#define TEST_NUMBER 3

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
test_at_range_out(std::vector<TYPE> &vec_std, ft::vector<TYPE> &vec_ft, int random)
{
	(void)random;
	bool ft(0), std(0);
	try
	{
		vec_std.at(vec_ft.size() + 1);
	}
	catch (std::exception &e)
	{
		std = 1;
	}
	try
	{
		vec_ft.at(vec_ft.size() + 1);
	}
	catch (std::exception &e)
	{
		ft = 1;
	}
	Tdd::expected(std, ft, "bool at() out of range");
}

template <typename TYPE>
static void
test_pop_back(std::vector<TYPE> &vec_std, ft::vector<TYPE> &vec_ft, int random)
{
	section("pop_back()");
	(void)random;

	/* avoid a segmenation fault
	 * the std::vector do not check there is a last element before to destroy it
	 */
	if (vec_ft.empty())
		return;
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
	f[2] = &test_at_range_out<TYPE>;

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
		title("test vector 2.0 : new test");
		start_test<int>(i);
		start_test<Awesome>(i);
	}

	return;
}
