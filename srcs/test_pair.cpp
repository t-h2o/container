#include "Pair.hpp"
#include "color.hpp"
#include <iostream>

static void
pair_one(void)
{
	ft::pair<int, int>	pair_ft(10, 42);
	std::pair<int, int> pair_std(10, 42);
}

void
test_pair(void)
{
	title("Pair 1");
	pair_one();
}
