#include "Awesome.hpp"
#include "Iterator.hpp"
#include "Vector.hpp"
#include "color.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

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
	ft::iterator<T>					  it_ft(vec_ft.begin());

	EXPECT_EQ(*it_ft, *it_std);

	for (size_t i = 0; i < vec_std.size(); ++i)
		EXPECT_EQ(it_ft[i], it_std[i]);

	for (it_ft = vec_ft.begin(); it_ft != vec_ft.end(); ++it_ft)
		std::cout << *it_ft << std::endl;
}

template <typename T>
static void
test_copy_equal(std::vector<T> &vec_std, ft::vector<T> &vec_ft)
{
	expect_equal(vec_std, vec_ft);

	{
		ft::vector<T> vec_ft_copy;
		vec_ft_copy = vec_ft;
		expect_equal(vec_std, vec_ft_copy);
	}
	{
		ft::vector<T> vec_ft_copy(vec_ft);
		expect_equal(vec_std, vec_ft_copy);
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
	vec_ft.erase(3);
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
	vec_ft.erase(1);
	vec_std.erase(vec_std.begin() + 1);
	test_copy_equal(vec_std, vec_ft);

	section("erase(1);");
	vec_ft.erase(1);
	vec_std.erase(vec_std.begin() + 1);
	test_copy_equal(vec_std, vec_ft);

	section("erase(0);");
	vec_ft.erase(0);
	vec_std.erase(vec_std.begin() + 0);
	test_copy_equal(vec_std, vec_ft);
}

template <typename T>
static void
scenario_four(void)
{
	ft::vector<T>  vec_ft;
	std::vector<T> vec_std;

	vec_std.assign(2, 42);
	vec_ft.assign(2, 42);

	typename std::vector<T>::iterator it_std;
	ft::iterator<T>					  it_ft;

	it_std = vec_std.begin();
	it_ft = vec_ft.begin();

	std::cout << "0: " << it_std[0] << std::endl;
	std::cout << "1: " << it_std[1] << std::endl;

	std::cout << "0: " << it_ft[0] << std::endl;
	std::cout << "1: " << it_ft[1] << std::endl;
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

	return 0;
}
