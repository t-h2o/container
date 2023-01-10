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

template <typename T1, typename T2>
void
erase_map(T1 const &key, std::map<T1, T2> &map_std, ft::map<T1, T2> &map_ft)
{
	map_ft.erase(key);
	map_std.erase(key);

	expected_equal(map_std, map_ft);
}

template <typename T1, typename T2>
void
insert_map(int n, std::map<T1, T2> &map_std, ft::map<T1, T2> &map_ft)
{
	map_ft[n] = "";
	map_std[n] = "";

	expected_equal(map_std, map_ft);
}

void
map_one(void)
{
	section("default constructor int, int");
	std::map<int, std::string> map_std;
	ft::map<int, std::string>  map_ft;

	section("Init new pair 3 => ");
	insert_map(3, map_std, map_ft);

	section("Init new pair 1 => ");
	insert_map(1, map_std, map_ft);

	section("Init new pair 5 => ");
	insert_map(5, map_std, map_ft);

	section("(Two red) Init new pair 7 => ");
	insert_map(7, map_std, map_ft);

	section("(Two red) Init new pair 6 => ");
	insert_map(6, map_std, map_ft);

	section("(Two red) Init new pair 8 => ");
	insert_map(8, map_std, map_ft);

	section("(Two red) Init new pair 9 => ");
	insert_map(9, map_std, map_ft);

	section("(Two red) Init new pair 10 => ");
	insert_map(10, map_std, map_ft);
}

void
map_left(void)
{
	section("default constructor int, int");
	std::map<int, std::string> map_std;
	ft::map<int, std::string>  map_ft;

	section("Init new pair 16 => ");
	insert_map(16, map_std, map_ft);

	section("Init new pair 15 => ");
	insert_map(15, map_std, map_ft);

	section("Init new pair 14 => ");
	insert_map(14, map_std, map_ft);

	section("Init new pair 13 => ");
	insert_map(13, map_std, map_ft);

	section("Init new pair 12 => ");
	insert_map(12, map_std, map_ft);

	section("Init new pair 11 => ");
	insert_map(11, map_std, map_ft);

	section("Init new pair 10 => ");
	insert_map(10, map_std, map_ft);

	section("Init new pair 9 => ");
	insert_map(9, map_std, map_ft);

	section("Init new pair 8 => ");
	insert_map(8, map_std, map_ft);

	section("Init new pair 7 => ");
	insert_map(7, map_std, map_ft);

	section("Init new pair 6 => ");
	insert_map(6, map_std, map_ft);

	section("Init new pair 5 => ");
	insert_map(5, map_std, map_ft);

	section("Init new pair 4 => ");
	insert_map(4, map_std, map_ft);

	section("Init new pair 3 => ");
	insert_map(3, map_std, map_ft);

	section("Init new pair 2 => ");
	insert_map(2, map_std, map_ft);

	section("Init new pair 1 => ");
	insert_map(1, map_std, map_ft);
}

void
map_right(void)
{
	section("default constructor int, int");
	std::map<int, std::string> map_std;
	ft::map<int, std::string>  map_ft;

	section("Init new pair 1 => ");
	insert_map(1, map_std, map_ft);

	section("Init new pair 2 => ");
	insert_map(2, map_std, map_ft);

	section("Init new pair 3 => ");
	insert_map(3, map_std, map_ft);

	section("Init new pair 4 => ");
	insert_map(4, map_std, map_ft);

	section("Init new pair 5 => ");
	insert_map(5, map_std, map_ft);

	map_ft.print_tree();

	section("erase 5");
	erase_map(5, map_std, map_ft);
	map_ft.print_tree();

	return;

	section("Init new pair 6 => ");
	insert_map(6, map_std, map_ft);

	section("Init new pair 7 => ");
	insert_map(7, map_std, map_ft);

	section("Init new pair 8 => ");
	insert_map(8, map_std, map_ft);

	section("Init new pair 9 => ");
	insert_map(9, map_std, map_ft);

	section("Init new pair 10 => ");
	insert_map(10, map_std, map_ft);

	section("Init new pair 11 => ");
	insert_map(11, map_std, map_ft);

	section("Init new pair 12 => ");
	insert_map(12, map_std, map_ft);

	section("Init new pair 13 => ");
	insert_map(13, map_std, map_ft);

	section("Init new pair 14 => ");
	insert_map(14, map_std, map_ft);

	section("Init new pair 15 => ");
	insert_map(15, map_std, map_ft);

	section("Init new pair 16 => ");
	insert_map(16, map_std, map_ft);
}
void
map_map(void)
{
	section("default constructor int, int");
	std::map<int, std::string> map_std;
	ft::map<int, std::string>  map_ft;

	std::pair<int, std::string> pair_std(23, "1234");
	ft::pair<int, std::string>	pair_ft(23, "1234");

	map_std.insert(pair_std);
	map_ft.insert(pair_ft);

	erase_map(23, map_std, map_ft);

	pair_std.second = "0987";
	pair_ft.second = "0987";

	map_std.insert(pair_std);
	map_ft.insert(pair_ft);

	section("Init new pair 12 => ");
	insert_map(12, map_std, map_ft);

	section("Init new pair 13 => ");
	insert_map(13, map_std, map_ft);

	section("Init new pair 14 => ");
	insert_map(14, map_std, map_ft);

	section("Init new pair 15 => ");
	insert_map(15, map_std, map_ft);

	section("Init new pair 16 => ");
	insert_map(16, map_std, map_ft);

	map_ft.print_tree();
}

void
test_map(void)
{
	//	title("Map one");
	//	map_one();
	//
	//	title("Map left");
	//	map_left();

	title("Map right");
	map_right();

	//	title("Map map");
	//	map_map();
}
