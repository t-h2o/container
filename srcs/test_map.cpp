#include "Awesome.hpp"
#include "Iterator.hpp"
#include "Map.hpp"
#include "color.hpp"
#include <gtest/gtest.h>
#include <iostream>

static void
map_one(void)
{
	section("test");

	ft::map<int, int> tree;

	tree[42] = 100;
	tree[12] = 200;
}

void
test_map(void)
{
	title("Pair 1");
	map_one();
}
