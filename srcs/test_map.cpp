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
map_left(void)
{
	section("default constructor int, int");
	std::map<int, std::string> map_std;
	ft::map<int, std::string>  map_ft;

	for (int insert = 20; insert > 0; --insert)
	{
		std::string message = "insert: " + std::to_string(insert);
		section(message);
		insert_map(insert, map_std, map_ft);
	}

	map_ft.print_tree();
}

void
map_right(void)
{
	section("default constructor int, int");
	std::map<int, std::string> map_std;
	ft::map<int, std::string>  map_ft;

	for (int insert = 0; insert < 20; ++insert)
	{
		std::string message = "insert: " + std::to_string(insert);
		section(message);
		insert_map(insert, map_std, map_ft);
	}

	map_ft.print_tree();
}

void
map_rand(unsigned int seed)
{
	section("default constructor int, int");
	std::map<int, std::string> map_std;
	ft::map<int, std::string>  map_ft;

	srand(seed);
	for (int i = 0; i < 20; ++i)
	{
		unsigned int random = rand() % 100;
		std::string	 a = "insert: " + std::to_string(random);
		section(a);
		insert_map(random, map_std, map_ft);
	}
	map_ft.print_tree();
}

void
test_map(void)
{
	title("Map left");
	map_left();

	title("Map right");
	map_right();

	for (int i = 0; i < 100; ++i)
	{
		std::string message = "Map random: " + std::to_string(i);
		title(message);
		map_rand(i);
	}
}
