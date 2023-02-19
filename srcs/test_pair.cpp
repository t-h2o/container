#include "Tdd.hpp"
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

static void
pair_four(void)
{
	ft::pair<char, int>	 pair_ft;
	std::pair<char, int> pair_std;

	char c_ = 'a';
	int	 i_ = 45;

	pair_ft = ft::make_pair(c_, i_);
	pair_std = std::make_pair(c_, i_);
	Tdd::expected(pair_ft.first, pair_std.first, "make pair");
	Tdd::expected(pair_ft.second, pair_std.second, "make pair");

	ft::pair<char, int> *ptr_pait_ft = &pair_ft;
	std::cout << ptr_pait_ft->first;
	ptr_pait_ft->first = 'v'; /* compile */

	const ft::pair<char, int> *const_ptr_pait_ft = &pair_ft;
	std::cout << const_ptr_pait_ft->first;
	// const_ptr_pait_ft->first = 'v'; /* do not compile */

	ft::pair<char, int> const *ptr_const_pait_ft = &pair_ft;
	std::cout << ptr_const_pait_ft->first;
	// ptr_const_pait_ft->first = 'v'; /* do not compile */
}

void
test_pair(void)
{
	title("Pair 1");
	pair_one();

	title("Pair 2");
	pair_two();

	title("pair 3");
	pair_tree();

	title("pair 4");
	pair_four();
}
