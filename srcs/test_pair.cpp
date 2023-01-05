#include "Pair.hpp"
#include "color.hpp"
#include <iostream>

static void
pair_two(void)
{
	ft::pair<int, int>	pair_ft_1(10, 42);
	std::pair<int, int> pair_std_1(10, 42);

	ft::pair<int, int>	pair_ft_2(1234, 777);
	std::pair<int, int> pair_std_2(1234, 777);

	pair_ft_2.swap(pair_ft_1);
	pair_std_2.swap(pair_std_1);
}

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

	title("Pair 2");
	pair_two();
}
