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

	section("Init new pair 1 => ");

	map_ft[1] = "";
	map_std[1] = "";

	expected_equal(map_std, map_ft);

	section("Init new pair 5 => ");

	map_ft[5] = "";
	map_std[5] = "";

	expected_equal(map_std, map_ft);

	section("(Two red) Init new pair 7 => ");

	map_ft[7] = "";
	map_std[7] = "";

	expected_equal(map_std, map_ft);

	section("(Two red) Init new pair 6 => ");

	map_ft[6] = "";
	map_std[6] = "";

	expected_equal(map_std, map_ft);

	section("(Two red) Init new pair 8 => ");

	map_ft[8] = "";
	map_std[8] = "";

	expected_equal(map_std, map_ft);

	section("(Two red) Init new pair 9 => ");

	map_ft[9] = "";
	map_std[9] = "";

	expected_equal(map_std, map_ft);

	section("(Two red) Init new pair 10 => ");

	map_ft[10] = "";
	map_std[10] = "";

	expected_equal(map_std, map_ft);
}

static void
map_two(void)
{
	section("default constructor int, int");
	std::map<int, std::string> map_std;
	ft::map<int, std::string>  map_ft;

	section("Init new pair 9 ");

	map_ft[9] = "";
	map_std[9] = "";

	expected_equal(map_std, map_ft);

	section("Init new pair 8 ");

	map_ft[8] = "";
	map_std[8] = "";

	expected_equal(map_std, map_ft);

	section("Init new pair 7 ");

	map_ft[7] = "";
	map_std[7] = "";

	expected_equal(map_std, map_ft);

	section("Init new pair 6 ");

	map_ft[6] = "";
	map_std[6] = "";

	expected_equal(map_std, map_ft);

	section("Init new pair 5 ");

	map_ft[5] = "";
	map_std[5] = "";

	expected_equal(map_std, map_ft);
}

void
test_map(void)
{
	title("Map 1");
	map_one();

	title("Map 2");
	map_two();
}
