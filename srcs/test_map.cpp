#include "Awesome.hpp"
#include "Iterator.hpp"
#include "Tdd.hpp"
#include "color.hpp"
#include "map.hpp"
#include "to_string.hpp"
#include <iostream>
#include <map>
#include <stdlib.h>
#include <vector>

#define TEST_NUMBER 10
#define TREE_SIZE 30
#define MAX_NUMBER 100

template <typename T1, typename T2>
static void
expected_equal(std::map<T1, T2> &map_std, ft::map<T1, T2> &map_ft)
{
	Tdd::expected(map_std.empty(), map_ft.empty());
	Tdd::expected(map_std.size(), map_ft.size());
	if (map_ft.empty())
		return;
	{
		typename ft::map<T1, T2>::iterator	it_ft = map_ft.begin();
		typename std::map<T1, T2>::iterator it_std = map_std.begin();
		Tdd::expected((*it_std).first, (*it_ft).first);

		bool end_ft;
		bool end_std;
		do
		{
			Tdd::expected((*it_std).first, (*it_ft).first);
			++it_ft;
			++it_std;
			end_ft = it_ft != map_ft.end();
			end_std = it_std != map_std.end();
			Tdd::expected(end_std, end_ft, "bool end");
		} while (end_ft);
		--it_ft;
		--it_std;
		do
		{
			Tdd::expected((*it_std).first, (*it_ft).first);
			--it_ft;
			--it_std;
			end_ft = it_ft != map_ft.begin();
			end_std = it_std != map_std.begin();
			Tdd::expected(end_std, end_ft, "bool end");
		} while (end_ft);
	}
	{
		typename ft::map<T1, T2>::const_iterator  it_ft = map_ft.begin();
		typename std::map<T1, T2>::const_iterator it_std = map_std.begin();
		Tdd::expected((*it_std).first, (*it_ft).first);

		bool end_ft;
		bool end_std;
		do
		{
			Tdd::expected((*it_std).first, (*it_ft).first);
			++it_ft;
			++it_std;
			end_ft = it_ft != map_ft.end();
			end_std = it_std != map_std.end();
			Tdd::expected(end_std, end_ft, "bool end");
		} while (end_ft);
		--it_ft;
		--it_std;
		do
		{
			Tdd::expected((*it_std).first, (*it_ft).first);
			--it_ft;
			--it_std;
			end_ft = it_ft != map_ft.begin();
			end_std = it_std != map_std.begin();
			Tdd::expected(end_std, end_ft, "bool end");
		} while (end_ft);
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
		std::string message = "insert: " + ft::to_string(insert);
		section(message);
		insert_map(insert, map_std, map_ft);
	}

	for (int remove = 20; remove > 0; --remove)
	{
		std::string a = "remove: " + ft::to_string(remove);
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
		std::string message = "insert: " + ft::to_string(insert);
		section(message);
		insert_map(insert, map_std, map_ft);
	}

	for (int remove = 20; remove > 0; --remove)
	{
		std::string a = "remove: " + ft::to_string(remove);
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
		std::string	 a = "insert: " + ft::to_string(random);
		section(a);
		insert_map(random, map_std, map_ft);
		key_list.push_back(random);
	}
	while (!key_list.empty())
	{
		unsigned int random = rand() % MAX_NUMBER;
		unsigned int position = random % key_list.size();
		int			 remove = key_list.at(position);
		std::string	 a = "remove: " + ft::to_string(remove);
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
		std::string message = "Map random: " + ft::to_string(i);
		title(message);
		map_rand(i);
	}
}
