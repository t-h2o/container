#include "Pair.hpp"
#include "color.hpp"
#include <iostream>

static void
pair_one(void)
{
	{
		ft::pair<int, int>	pair_ft(10, 42);
		std::pair<int, int> pair_std(10, 42);

		ft::pair<int, int>	pair_ft_copy(pair_ft);
		std::pair<int, int> pair_std_copy(pair_std);
	}

	{
		ft::pair<int, int>	pair_ft;
		std::pair<int, int> pair_std;

		ft::pair<int, int>	pair_ft_copy(pair_ft);
		std::pair<int, int> pair_std_copy(pair_std);
	}

	{
		ft::pair<int, int>	pair_ft(10, 42);
		std::pair<int, int> pair_std(10, 42);

		ft::pair<int, int>	pair_ft_copy = pair_ft;
		std::pair<int, int> pair_std_copy = pair_std;

		(void)pair_ft_copy;
		(void)pair_std_copy;
	}
}

void
test_pair(void)
{
	title("Pair 1");
	pair_one();
}
