#include "Awesome.hpp"
#include "Iterator.hpp"
#include "Map.hpp"
#include "color.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <map>

template <typename T1, typename T2>
static void
expected_equal(std::map<T1, T2> &map_std, ft::map<T1, T2> &map_ft)
{
	EXPECT_EQ(map_std.empty(), map_ft.empty());
}

static void
map_one(void)
{
	section("test");

	std::map<int, int> map_std;
	ft::map<int, int>  map_ft;

	expected_equal(map_std, map_ft);

	map_ft[42] = 100;
	map_std[42] = 100;

	expected_equal(map_std, map_ft);

	map_ft[12] = 200;
	map_std[12] = 200;

	expected_equal(map_std, map_ft);
}

void
test_map(void)
{
	title("Pair 1");
	map_one();
}
