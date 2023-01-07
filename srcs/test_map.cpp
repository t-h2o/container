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
	EXPECT_EQ(map_std.size(), map_ft.size());
}

static void
map_one(void)
{
	section("default constructor int, int");
	std::map<int, std::string> map_std;
	ft::map<int, std::string>  map_ft;

	section("Init new pair 3 => ");

	map_ft[3] = "";
	map_std[3] = "";

	expected_equal(map_std, map_ft);
	map_ft.print_tree();

	section("Init new pair 1 => ");

	map_ft[1] = "";
	map_std[1] = "";

	expected_equal(map_std, map_ft);
	map_ft.print_tree();

	section("Init new pair 5 => ");

	map_ft[5] = "";
	map_std[5] = "";

	expected_equal(map_std, map_ft);
	map_ft.print_tree();

	section("(Two red) Init new pair 7 => ");

	map_ft[7] = "";
	map_std[7] = "";

	expected_equal(map_std, map_ft);
	map_ft.print_tree();
}

void
test_map(void)
{
	title("Pair 1");
	map_one();
}
