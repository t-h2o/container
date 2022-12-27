#include "Awesome.hpp"
#include "Vector.hpp"
#include "color.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <vector>

template <typename T>
static void
expect_equal(std::vector<T> &vec_std, Vector<T> &vec_ft)
{
	EXPECT_EQ(vec_ft.size(), vec_std.size());
	EXPECT_EQ(vec_ft.max_size(), vec_std.max_size());
	EXPECT_EQ(vec_ft.capacity(), vec_std.capacity());
	EXPECT_EQ(vec_ft.empty(), vec_std.empty());

	T const *data_std = vec_std.data();
	T const *data_ft = vec_ft.data();

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
	{
		Vector<T> vec_ft_copy(vec_ft);
		expect_equal(vec_std, vec_ft_copy);
	}
}

template <typename T>
static void
test_comparison(void)
{
	section("Test with comparison");

	std::vector<T> vec_std;
	Vector<T>	   vec_ft;

	test_copy_equal(vec_std, vec_ft);

	vec_ft.assign(7, 100);
	vec_std.assign(7, 100);
	test_copy_equal(vec_std, vec_ft);

	vec_ft.assign(3, 200);
	vec_std.assign(3, 200);
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

int
main(void)
{
	title("Main");

	test_comparison<int>();
	test_comparison<Awesome>();

	return 0;
}
