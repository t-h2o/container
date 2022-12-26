#include "Awesome.hpp"
#include "Vector.hpp"
#include "color.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

static void
test_awesome(void)
{
	section("Test with Awesome class");

	Awesome awesome;

	{
		Vector<Awesome> vec_ft;
		vec_ft.assign(5, awesome);
		vec_ft.pop_back();

		Vector<Awesome> vec_ft_copy;
		vec_ft[0].set_number(42);
		vec_ft[2].set_number(21);
		section("copy");
		vec_ft = vec_ft;
		vec_ft_copy = vec_ft;

		std::cout << "ft" << vec_ft;
		std::cout << "copy" << vec_ft_copy;

		vec_ft.push_back(1);
		vec_ft.push_back(2);

		std::cout << "ft" << vec_ft;
		std::cout << "copy" << vec_ft_copy;

		section("swap");
		vec_ft.swap(vec_ft_copy);

		std::cout << "ft" << vec_ft;
		std::cout << "copy" << vec_ft_copy;
	}
}

template <typename T>
static void
expect_equal(std::vector<T> &vec_std, Vector<T> &vec_ft)
{
	EXPECT_EQ(vec_ft.size(), vec_std.size());
	EXPECT_EQ(vec_ft.max_size(), vec_std.max_size());
	EXPECT_EQ(vec_ft.capacity(), vec_std.capacity());
	EXPECT_EQ(vec_ft.empty(), vec_std.empty());

	int const *data_std = vec_std.data();
	int const *data_ft = vec_ft.data();

	for (size_t i = 0; i < vec_std.size(); ++i)
		EXPECT_EQ(data_ft[i], data_std[i]);
}

template <typename T>
static void
test_copy_equal(std::vector<T> &vec_std, Vector<T> &vec_ft)
{
	expect_equal(vec_std, vec_ft);

	{
		Vector<T> vec_ft_copy;
		vec_ft_copy = vec_ft;
		expect_equal(vec_std, vec_ft_copy);
	}
}

static void
test_comparison(void)
{
	section("Test with comparison");

	std::vector<int> vec_std;
	Vector<int>		 vec_ft;

	test_copy_equal(vec_std, vec_ft);

	vec_ft.assign(7, 100);
	vec_std.assign(7, 100);
	test_copy_equal(vec_std, vec_ft);

	vec_ft.pop_back();
	vec_std.pop_back();
	test_copy_equal(vec_std, vec_ft);

	vec_ft.push_back(12);
	vec_std.push_back(12);
	test_copy_equal(vec_std, vec_ft);

	vec_ft.push_back(13);
	vec_std.push_back(13);
	test_copy_equal(vec_std, vec_ft);

	vec_ft.clear();
	vec_std.clear();
	test_copy_equal(vec_std, vec_ft);

	vec_ft.push_back(13);
	vec_std.push_back(13);
	test_copy_equal(vec_std, vec_ft);
}

static void
test_my_vector(void)
{
	Vector<int> vec;

	section("assign 7 times the value 100");
	vec.assign(7, 100);

	section("print vec");
	std::cout << vec << std::endl;

	section("add 1, 2, 3...");
	for (unsigned long i = 0; i < vec.size(); i++)
		vec[i] += i;

	section("print vec");
	std::cout << vec << std::endl;

	section("print the 3th number");
	std::cout << vec[3] << std::endl;

	section("print the front number");
	std::cout << vec.front() << std::endl;

	section("print the back number");
	std::cout << vec.back() << std::endl;

	section("pop back number");
	vec.pop_back();

	section("print vec");
	std::cout << vec << std::endl;

	section("print the back number");
	std::cout << vec.back() << std::endl;

	section("try an overrange number");
	try
	{
		std::cout << "vec at    2 : " << vec.at(2) << std::endl;
		std::cout << "vec at 1234 : " << vec.at(1234) << std::endl;
	}
	catch (std::exception &e)
	{
		print_exception(e);
	}

	section("print the max size");
	std::cout << vec.max_size() << std::endl;

	section("push back 42");
	int myint = 42;
	vec.push_back(myint);

	section("print vec");
	std::cout << vec << std::endl;
}

static void
test_vector(void)
{
	std::vector<int> vec;

	section("assign 7 times the value 100");
	vec.assign(11, 100);

	section("print the 3th number");
	std::cout << vec[3] << std::endl;
}

int
main(void)
{
	title("Main");

	test_my_vector();
	test_vector();
	test_comparison();
	test_awesome();

	return 0;
}
