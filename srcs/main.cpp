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

	section("assign(5, 5);");
	vec_ft.assign(5, 5);
	vec_std.assign(5, 5);
	test_copy_equal(vec_std, vec_ft);

	section("resize(777);");
	vec_ft.resize(777);
	vec_std.resize(777);
	test_copy_equal(vec_std, vec_ft);

	section("resize(2);");
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
}

template <typename T>
static void
scenario_eight(void)
{
	ft::vector<T>  vec_ft;
	std::vector<T> vec_std;

	push_back_ten(vec_std, vec_ft);

	section("push_back(42);");
	vec_ft.push_back(42);
	vec_std.push_back(42);
	test_copy_equal(vec_std, vec_ft);

	section("insert(vec_ft.begin() + 1, 1234);");
	vec_ft.insert(vec_ft.begin() + 1, 1234);
	vec_std.insert(vec_std.begin() + 1, 1234);
	test_copy_equal(vec_std, vec_ft);

	section("insert(vec_ft.begin(), -1);");
	vec_ft.insert(vec_ft.begin(), -1);
	vec_std.insert(vec_std.begin(), -1);
	test_copy_equal(vec_std, vec_ft);

	section("shrink_to_fit();");
	vec_ft.shrink_to_fit();
	vec_std.shrink_to_fit();
	test_copy_equal(vec_std, vec_ft);

	section("insert(vec_ft.begin() + 1, 777);");
	vec_ft.insert(vec_ft.begin() + 1, 777);
	vec_std.insert(vec_std.begin() + 1, 777);
	test_copy_equal(vec_std, vec_ft);

	section("insert(vec_ft.begin() + 5, 3, 333);");
	vec_ft.insert(vec_ft.begin() + 5, 3, 333);
	vec_std.insert(vec_std.begin() + 5, 3, 333);
	test_copy_equal(vec_std, vec_ft);

	section("shrink_to_fit();");
	vec_ft.shrink_to_fit();
	vec_std.shrink_to_fit();
	test_copy_equal(vec_std, vec_ft);

	section("insert(vec_ft.begin() + 10, 2, -999);");
	vec_ft.insert(vec_ft.begin() + 10, 2, -999);
	vec_std.insert(vec_std.begin() + 10, 2, -999);
	test_copy_equal(vec_std, vec_ft);

	section("insert(vec_ft.begin() + 10, 99, -999);");
	vec_ft.insert(vec_ft.begin() + 10, 99, -999);
	vec_std.insert(vec_std.begin() + 10, 99, -999);
	test_copy_equal(vec_std, vec_ft);
}

template <typename T>
static void
scenario_nine(void)
{
	{
		section("Constructor fill (4, 42);");
		ft::vector<T>  vec_ft(4, 42);
		std::vector<T> vec_std(4, 42);

		test_copy_equal(vec_std, vec_ft);

		section("push_back(0);");
		vec_ft.push_back(0);
		vec_std.push_back(0);
		test_copy_equal(vec_std, vec_ft);

		section("Constructor range (vec_ft.begin(), vec_ft.end();");
		ft::vector<T>  vec_ft_copy(vec_ft.begin(), vec_ft.end());
		std::vector<T> vec_std_copy(vec_std.begin(), vec_std.end());

		test_copy_equal(vec_std_copy, vec_ft_copy);

		section("push_back(42);");
		vec_ft_copy.push_back(42);
		vec_std_copy.push_back(42);
		test_copy_equal(vec_std_copy, vec_ft_copy);
	}
	{
		section("Constructor fill (0, 42);");
		ft::vector<T>  vec_ft(0, 42);
		std::vector<T> vec_std(0, 42);

		test_copy_equal(vec_std, vec_ft);

		section("Constructor range (vec_ft.begin(), vec_ft.end();");
		ft::vector<T>  vec_ft_copy(vec_ft.begin(), vec_ft.end());
		std::vector<T> vec_std_copy(vec_std.begin(), vec_std.end());

		test_copy_equal(vec_std_copy, vec_ft_copy);

		section("push_back(42);");
		vec_ft.push_back(42);
		vec_std.push_back(42);
		test_copy_equal(vec_std, vec_ft);
	}
}

template <typename T>
static void
scenario_ten(void)
{
	ft::vector<T>  vec_ft;
	std::vector<T> vec_std;

	push_back_ten(vec_std, vec_ft);
	test_copy_equal(vec_std, vec_ft);

	{
		section("default constructor");
		ft::vector<T>  vec_ft_copy;
		std::vector<T> vec_std_copy;

		section("vec_ft_copy.assign(vec_ft.begin(), vec_ft.end();");
		vec_ft_copy.assign(vec_ft.begin(), vec_ft.end());
		vec_std_copy.assign(vec_std.begin(), vec_std.end());

		test_copy_equal(vec_std_copy, vec_ft_copy);
	}

	{
		section("(big) fill constructor");
		ft::vector<T>  vec_ft_copy(42, 42);
		std::vector<T> vec_std_copy(42, 42);
		test_copy_equal(vec_std_copy, vec_ft_copy);

		section("vec_ft_copy.assign(vec_ft.begin() + 1, vec_ft.end();");
		vec_ft_copy.assign(vec_ft.begin() + 1, vec_ft.end());
		vec_std_copy.assign(vec_std.begin() + 1, vec_std.end());

		test_copy_equal(vec_std_copy, vec_ft_copy);
	}

	{
		section("(little) fill constructor");
		ft::vector<T>  vec_ft_copy(1, 42);
		std::vector<T> vec_std_copy(1, 42);
		test_copy_equal(vec_std_copy, vec_ft_copy);

		section("vec_ft_copy.assign(vec_ft.begin() + 1, vec_ft.end();");
		vec_ft_copy.assign(vec_ft.begin() + 1, vec_ft.end());
		vec_std_copy.assign(vec_std.begin() + 1, vec_std.end());

		test_copy_equal(vec_std_copy, vec_ft_copy);
	}
}

int
main(void)
{
	title("Main");

	title("Scenario 1: int");
	scenario_one<int>();
	title("Scenario 1: Awesome");
	scenario_one<Awesome>();

	title("Scenario 2: int");
	scenario_two<int>();
	title("Scenario 2: Awesome");
	scenario_two<Awesome>();

	title("Scenario 3: int");
	scenario_tree<int>();
	title("Scenario 3: Awesome");
	scenario_tree<Awesome>();

	title("Scenario 4: int");
	scenario_four<int>();
	title("Scenario 4: Awesome");
	scenario_four<Awesome>();

	title("Scenario 5: int");
	scenario_five<int>();
	title("Scenario 5: Awesome");
	scenario_five<Awesome>();

	title("Scenario 6: int");
	scenario_six<int>();
	title("Scenario 6: Awesome");
	scenario_six<Awesome>();

	title("Scenario 7: int");
	scenario_seven<int>();
	title("Scenario 7: Awesome");
	scenario_six<Awesome>();

	title("Scenario 8: int");
	scenario_eight<int>();
	title("Scenario 8: Awesome");
	scenario_eight<Awesome>();

	title("Scenario 9: int");
	scenario_nine<int>();
	title("Scenario 9: Awesome");
	scenario_nine<Awesome>();

	title("Scenario 10: int");
	scenario_ten<int>();
	title("Scenario 10: Awesome");
	scenario_ten<Awesome>();

	return 0;
}
