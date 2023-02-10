#include "color.hpp"
#include "pair.hpp"
#include <iostream>

static void
pair_two(void)
{
	ft::pair<int, int>	pair_ft_1(10, 42);
	std::pair<int, int> pair_std_1(10, 42);

	ft::pair<int, int>	pair_ft_2(1234, 777);
	std::pair<int, int> pair_std_2(1234, 777);
}

static void
pair_one(void)
{
	{
		ft::pair<int, int>	pair_ft(10, 42);
		std::pair<int, int> pair_std(10, 42);

		ft::pair<int, int>	pair_ft_copy(pair_ft);
		std::pair<int, int> pair_std_copy(pair_std);
		(void)pair_std_copy;
	}

	{
		ft::pair<int, int>	pair_ft;
		std::pair<int, int> pair_std;

		ft::pair<int, int>	pair_ft_copy(pair_ft);
		std::pair<int, int> pair_std_copy(pair_std);
		(void)pair_std_copy;
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

static void
pair_tree(void)
{
	ft::pair<char, int>	 pair_ft;
	std::pair<char, int> pair_std;

	pair_ft.first = 'a';
	pair_std.first = 'a';

	pair_ft.second = 42;
	pair_std.second = 42;
}

void
test_pair(void)
{
	title("Pair 1");
	pair_one();

	title("Pair 2");
	pair_two();

	title("Pair 3");
	pair_tree();
}
