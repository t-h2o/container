#include "Awesome.hpp"
#include "Iterator.hpp"
#include "Vector.hpp"
#include "color.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

template <typename T>
static void
push_back_ten(std::vector<T> &vec_std, ft::vector<T> &vec_ft)
{
	for (int i = 0; i < 10; i++)
	{
		vec_std.push_back(i * 10);
		vec_ft.push_back(i * 10);
	}
}

template <typename T>
static void
expect_equal(std::vector<T> &vec_std, ft::vector<T> &vec_ft)
{
	EXPECT_EQ(vec_ft.size(), vec_std.size());
	EXPECT_EQ(vec_ft.max_size(), vec_std.max_size());
	EXPECT_EQ(vec_ft.capacity(), vec_std.capacity());
	EXPECT_EQ(vec_ft.empty(), vec_std.empty());

	T const *data_std = vec_std.data();
	T const *data_ft = vec_ft.data();

	for (size_t i = 0; i < vec_std.size(); ++i)
		EXPECT_EQ(data_ft[i], data_std[i]);

	if (vec_ft.empty())
		return;

	typename std::vector<T>::iterator it_std(vec_std.begin());
	typename ft::vector<T>::iterator  it_ft(vec_ft.begin());

	EXPECT_EQ(*it_ft, *it_std);

	for (size_t i = 0; i < vec_std.size(); ++i)
		EXPECT_EQ(it_ft[i], it_std[i]);

	EXPECT_EQ(vec_ft.begin() > vec_ft.end(), vec_std.begin() > vec_std.end());
	EXPECT_EQ(vec_ft.begin() < vec_ft.end(), vec_std.begin() < vec_std.end());
	EXPECT_EQ(vec_ft.begin() >= vec_ft.end(),
			  vec_std.begin() >= vec_std.end());
	EXPECT_EQ(vec_ft.begin() <= vec_ft.end(),
			  vec_std.begin() <= vec_std.end());

	EXPECT_EQ(vec_ft.end() > vec_ft.end(), vec_std.end() > vec_std.end());
	EXPECT_EQ(vec_ft.end() < vec_ft.end(), vec_std.end() < vec_std.end());
	EXPECT_EQ(vec_ft.end() >= vec_ft.end(), vec_std.end() >= vec_std.end());
	EXPECT_EQ(vec_ft.end() <= vec_ft.end(), vec_std.end() <= vec_std.end());

	if (vec_ft.size() < 3)
		return;

	it_ft = vec_ft.begin();
	it_std = vec_std.begin();
	EXPECT_EQ(*(it_ft++), *(it_std++));
	EXPECT_EQ(*(++it_ft), *(++it_std));
	EXPECT_EQ(*(it_ft--), *(it_std--));
	EXPECT_EQ(*(--it_ft), *(--it_std));

	it_ft += 1;
	it_std += 1;
	EXPECT_EQ(*(it_ft), *(it_std));

	it_ft = it_ft + 1;
	it_std = it_std + 1;
	EXPECT_EQ(*(it_ft), *(it_std));

	it_ft -= 1;
	it_std -= 1;
	EXPECT_EQ(*(it_ft), *(it_std));

	it_ft = it_ft - 1;
	it_std = it_std - 1;
	EXPECT_EQ(*(it_ft), *(it_std));
}

template <typename T>
static void
test_copy_equal(std::vector<T> &vec_std, ft::vector<T> &vec_ft)
{
	section("\tnormal");
	expect_equal(vec_std, vec_ft);

	{
		std::vector<T> vec_std_copy;
		ft::vector<T>  vec_ft_copy;

		vec_ft_copy = vec_ft;
		vec_std_copy = vec_std;

		section("\toperator =");
		expect_equal(vec_std_copy, vec_ft_copy);
	}
	{
		section("\tcopy constructor");
		std::vector<T> vec_std_copy(vec_std);
		ft::vector<T>  vec_ft_copy(vec_ft);

		expect_equal(vec_std_copy, vec_ft_copy);
	}
}

template <typename T>
static void
scenario_one(void)
{
	section("Test with comparison");

	std::vector<T> vec_std;
	ft::vector<T>  vec_ft;

	test_copy_equal(vec_std, vec_ft);

	section("assign(7, 100);");
	vec_ft.assign(7, 100);
	vec_std.assign(7, 100);
	test_copy_equal(vec_std, vec_ft);

	section("assign(3, 200);");
	vec_ft.assign(3, 200);
	vec_std.assign(3, 200);
	test_copy_equal(vec_std, vec_ft);

	section("assign(12, 300);");
	vec_ft.assign(12, 300);
	vec_std.assign(12, 300);
	test_copy_equal(vec_std, vec_ft);

	section("pop_back;");
	vec_ft.pop_back();
	vec_std.pop_back();
	test_copy_equal(vec_std, vec_ft);

	section("push_back(12);");
	vec_ft.push_back(12);
	vec_std.push_back(12);
	test_copy_equal(vec_std, vec_ft);

	section("push_back(13);");
	vec_ft.push_back(13);
	vec_std.push_back(13);
	test_copy_equal(vec_std, vec_ft);

	section("clear();");
	vec_ft.clear();
	vec_std.clear();
	test_copy_equal(vec_std, vec_ft);

	section("push_back(13);");
	vec_ft.push_back(13);
	vec_std.push_back(13);
	test_copy_equal(vec_std, vec_ft);
}

template <typename T>
static void
scenario_two(void)
{
	section("Test with comparison");

	std::vector<T> vec_std;
	ft::vector<T>  vec_ft;

	test_copy_equal(vec_std, vec_ft);

	section("shrink_to_fit();");
	vec_ft.shrink_to_fit();
	vec_std.shrink_to_fit();
	test_copy_equal(vec_std, vec_ft);

	section("push_back(12);");
	vec_ft.push_back(12);
	vec_std.push_back(12);
	test_copy_equal(vec_std, vec_ft);

	section("push_back(2);");
	vec_ft.push_back(2);
	vec_std.push_back(2);
	test_copy_equal(vec_std, vec_ft);

	section("push_back(33);");
	vec_ft.push_back(33);
	vec_std.push_back(33);
	test_copy_equal(vec_std, vec_ft);

	section("assign(7, 100);");
	vec_ft.assign(7, 100);
	vec_std.assign(7, 100);
	test_copy_equal(vec_std, vec_ft);

	section("erase(3);");
	vec_ft.erase(vec_ft.begin() + 3);
	vec_std.erase(vec_std.begin() + 3);
	test_copy_equal(vec_std, vec_ft);

	section("shrink_to_fit();");
	vec_ft.shrink_to_fit();
	vec_std.shrink_to_fit();
	test_copy_equal(vec_std, vec_ft);

	section("pop_back;");
	vec_ft.pop_back();
	vec_std.pop_back();
	test_copy_equal(vec_std, vec_ft);

	section("shrink_to_fit();");
	vec_ft.shrink_to_fit();
	vec_std.shrink_to_fit();
	test_copy_equal(vec_std, vec_ft);
}

template <typename T>
static void
scenario_tree(void)
{
	section("Test with comparison");

	std::vector<T> vec_std;
	ft::vector<T>  vec_ft;

	test_copy_equal(vec_std, vec_ft);

	section("push_back(1);");
	vec_ft.push_back(1);
	vec_std.push_back(1);
	test_copy_equal(vec_std, vec_ft);

	section("push_back(22);");
	vec_ft.push_back(22);
	vec_std.push_back(22);
	test_copy_equal(vec_std, vec_ft);

	section("push_back(333);");
	vec_ft.push_back(333);
	vec_std.push_back(333);
	test_copy_equal(vec_std, vec_ft);

	section("erase(1);");
	vec_ft.erase(vec_ft.begin() + 1);
	vec_std.erase(vec_std.begin() + 1);
	test_copy_equal(vec_std, vec_ft);

	section("erase(1);");
	vec_ft.erase(vec_ft.begin() + 1);
	vec_std.erase(vec_std.begin() + 1);
	test_copy_equal(vec_std, vec_ft);

	section("erase(0);");
	vec_ft.erase(vec_ft.begin() + 0);
	vec_std.erase(vec_std.begin() + 0);
	test_copy_equal(vec_std, vec_ft);
}

template <typename T>
static void
scenario_four(void)
{
	ft::vector<T>  vec_ft;
	std::vector<T> vec_std;

	push_back_ten(vec_std, vec_ft);

	test_copy_equal(vec_std, vec_ft);

	{
		section("copy constructor");
		ft::vector<T>  vec_ft_copy(vec_ft);
		std::vector<T> vec_std_copy(vec_std);

		section("\tcopy");
		test_copy_equal(vec_std_copy, vec_ft_copy);

		section("push back 42");
		vec_ft.push_back(42);
		vec_std.push_back(42);

		section("\tnormal");
		test_copy_equal(vec_std, vec_ft);
		section("\tcopy");
		test_copy_equal(vec_std_copy, vec_ft_copy);

		section("operator =");
		vec_ft_copy = vec_ft;
		vec_std_copy = vec_std;
		test_copy_equal(vec_std, vec_ft);
		test_copy_equal(vec_std_copy, vec_ft_copy);
	}
}

template <typename T>
static void
scenario_five(void)
{
	ft::vector<T>  vec_ft;
	std::vector<T> vec_std;

	push_back_ten(vec_std, vec_ft);

	{
		ft::vector	v_ft_copy(vec_ft);
		std::vector v_std_copy(vec_std);

		v_ft_copy.erase(v_ft_copy.begin() + 1, v_ft_copy.end() - 1);
		v_std_copy.erase(v_std_copy.begin() + 1, v_std_copy.end() - 1);
		test_copy_equal(v_std_copy, v_ft_copy);
	}

	{
		ft::vector	v_ft_copy(vec_ft);
		std::vector v_std_copy(vec_std);

		v_ft_copy.erase(v_ft_copy.begin() + 1, v_ft_copy.end());
		v_std_copy.erase(v_std_copy.begin() + 1, v_std_copy.end());
		test_copy_equal(v_std_copy, v_ft_copy);
	}

	{
		ft::vector	v_ft_copy(vec_ft);
		std::vector v_std_copy(vec_std);

		v_ft_copy.erase(v_ft_copy.end() - 3, v_ft_copy.end());
		v_std_copy.erase(v_std_copy.end() - 3, v_std_copy.end());
		test_copy_equal(v_std_copy, v_ft_copy);
	}
}

template <typename T>
static void
scenario_six(void)
{
	ft::vector<T>  vec_ft;
	std::vector<T> vec_std;

	vec_ft.assign(5, 5);
	vec_std.assign(5, 5);
	test_copy_equal(vec_std, vec_ft);

	vec_ft.resize(7);
	vec_std.resize(7);
	test_copy_equal(vec_std, vec_ft);

	vec_ft.resize(2);
	vec_std.resize(2);
	test_copy_equal(vec_std, vec_ft);
}

template <typename T>
static void
scenario_seven(void)
{
	ft::vector<T>  vec_ft;
	std::vector<T> vec_std;

	vec_ft.assign(5, 5);
	vec_std.assign(5, 5);
	test_copy_equal(vec_std, vec_ft);

	vec_ft.reserve(3);
	vec_std.reserve(3);
	test_copy_equal(vec_std, vec_ft);

	vec_ft.reserve(7);
	vec_std.reserve(7);
	test_copy_equal(vec_std, vec_ft);

	vec_ft.push_back(1234);
	vec_std.push_back(1234);
	test_copy_equal(vec_std, vec_ft);
}

int
main(void)
{
	title("Main");

	title("Scenario 1");
	scenario_one<int>();
	scenario_one<Awesome>();

	title("Scenario 2");
	scenario_two<int>();
	scenario_two<Awesome>();

	title("Scenario 3");
	scenario_tree<int>();
	scenario_tree<Awesome>();

	title("Scenario 4");
	scenario_four<int>();
	scenario_four<Awesome>();

	title("Scenario 5");
	scenario_five<int>();
	scenario_five<Awesome>();

	title("Scenario 6");
	scenario_six<int>();
	scenario_six<Awesome>();

	title("Scenario 7");
	scenario_seven<int>();
	scenario_six<Awesome>();

	return 0;
}
