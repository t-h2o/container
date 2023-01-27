#include "Awesome.hpp"
#include "Iterator.hpp"
#include "Map.hpp"
#include "color.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <iterator>
#include <map>
#include <vector>

#define TEST_NUMBER 1
#define TREE_SIZE 100
#define MAX_NUMBER 1000

template <typename T1, typename T2>
static void
expected_equal(std::map<T1, T2> &map_std, ft::map<T1, T2> &map_ft)
{
	EXPECT_EQ(map_std.empty(), map_ft.empty());
	EXPECT_EQ(map_std.size(), map_ft.size());

	if (map_ft.empty())
		return;

	map_ft.print_tree();

	typename std::map<T1, T2>::iterator it_std = map_std.end();
	typename ft::map<T1, T2>::iterator	it_ft = map_ft.end();

	// EXPECT_EQ((*(--it_std)).first, (*it_ft).first);

	it_std = map_std.begin();
	it_ft = map_ft.begin();
	EXPECT_EQ((*it_std).first, (*it_ft).first);

	while (it_ft != map_ft.end())
	{
		std::cout << "it_std: " << (*it_std).first << std::endl;
		EXPECT_EQ((*it_std).first, (*it_ft).first);

		typename ft::map<T1, T2>::iterator it_ft_find = map_ft.find((*it_ft).first);
		EXPECT_EQ((*it_ft_find).first, (*it_ft).first);

		EXPECT_EQ(map_ft.count((*it_ft).first), map_std.count((*it_std).first));

		it_std++;
		it_ft++;
	}
	it_std--;
	it_ft--;

	while (it_ft != map_ft.begin() && !(it_ft == map_ft.begin()))
	{
		EXPECT_EQ((*it_std).first, (*it_ft).first);
		--it_std;
		--it_ft;
	}
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

	for (int remove = 20; remove > 0; --remove)
	{
		std::string a = "remove: " + std::to_string(remove);
		section(a);
		erase_map(remove, map_std, map_ft);
	}
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

	for (int remove = 20; remove > 0; --remove)
	{
		std::string a = "remove: " + std::to_string(remove);
		section(a);
		erase_map(remove, map_std, map_ft);
	}
}

void
map_rand(unsigned int seed)
{
	section("default constructor int, int");
	std::map<int, std::string> map_std;
	ft::map<int, std::string>  map_ft;

	std::vector<int> key_list;

	srand(seed);
	for (int i = 0; i < TREE_SIZE; ++i)
	{
		unsigned int random = rand() % MAX_NUMBER;
		std::string	 a = "insert: " + std::to_string(random);
		section(a);
		insert_map(random, map_std, map_ft);
		key_list.push_back(random);
	}
	while (!key_list.empty())
	{
		unsigned int random = rand() % MAX_NUMBER;
		unsigned int position = random % key_list.size();
		int			 remove = key_list.at(position);
		std::string	 a = "remove: " + std::to_string(remove);
		section(a);
		erase_map(remove, map_std, map_ft);
		key_list.erase(key_list.begin() + position);
	}
}

void
test_map(void)
{
	//	title("Map left");
	//	map_left();
	//
	//	title("Map right");
	//	map_right();

	for (int i = 0; i < TEST_NUMBER; ++i)
	{
		std::string message = "Map random: " + std::to_string(i);
		title(message);
		map_rand(i);
	}
}
