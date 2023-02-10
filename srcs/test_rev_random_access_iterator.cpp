#include "Awesome.hpp"
#include "Iterator.hpp"
#include "Tdd.hpp"
#include "color.hpp"
#include "vector.hpp"
#include <iostream>
#include <vector>

// #define STD

#ifdef STD
#define NAME_SPACE std
#else
#define NAME_SPACE ft
#endif

typedef struct s_simple
{
	int	 i;
	char c;
} t_simple;

template <typename _Vector>
static void
fill_simple(_Vector &simple)
{
	t_simple a;

	for (int i = 0; i < 26; ++i)
	{
		a.i = i;
		a.c = 'a' + i;
		simple.push_back(a);
	}
}

template <typename _Reverse_I>
static void
test_iterator(NAME_SPACE::vector<t_simple> &simple)
{
	_Reverse_I it_end(simple.rend());

	for (_Reverse_I it(simple.rbegin()); it != it_end; ++it)
		std::cout << ' ' << (*it).i;
	std::cout << std::endl;

	for (_Reverse_I it(simple.rbegin()); it != it_end; ++it)
		std::cout << ' ' << (*it).c;
	std::cout << std::endl;

	_Reverse_I it(simple.rbegin());
	for (int i = 0; i != it_end - it; ++i)
		std::cout << ' ' << it[i].c;
	std::cout << std::endl;

	{
		_Reverse_I asdf = it + 10;

		while (asdf != it_end)
		{
			std::cout << ' ' << asdf->c;
			++asdf;
		}
		std::cout << std::endl;

		while (asdf-- != it)
			std::cout << ' ' << asdf->c;
		std::cout << std::endl;
	}
	{
		_Reverse_I asdf = it;

		while (asdf != it_end - 10)
		{
			std::cout << ' ' << asdf->c;
			++asdf;
		}
		std::cout << std::endl;

		while (asdf-- != it)
			std::cout << ' ' << asdf->c;
		std::cout << std::endl;
	}
	{
		_Reverse_I asdf = it;

		while (asdf > it_end - 10)
		{
			std::cout << ' ' << asdf->c;
			asdf += 3;
		}
		std::cout << std::endl;

		while (it < asdf--)
		{
			std::cout << ' ' << asdf->c;
			std::cout << std::endl;
			asdf -= 3;
		}
	}
	{
		_Reverse_I asdf = it;

		while (asdf <= it_end - 10)
		{
			std::cout << ' ' << asdf->c;
			asdf += 3;
		}
		std::cout << std::endl;

		while (it <= asdf--)
			std::cout << ' ' << asdf->c;
		std::cout << std::endl;
	}
}

void
test_rev_random_access_iterator(void)
{
	NAME_SPACE::vector<t_simple> simple;

	fill_simple(simple);

#ifdef STD
	title("Test: reverse random access iterator with std");
#else
	title("Test: reverse random access iterator with ft");
#endif

	{
		section("Test: reverse_iterator");
		typedef NAME_SPACE::vector<t_simple>::reverse_iterator reverse_iterator;

		test_iterator<reverse_iterator>(simple);
	}
	{
		section("Test: const_reverse_iterator");
		typedef NAME_SPACE::vector<t_simple>::const_reverse_iterator reverse_iterator;

		test_iterator<reverse_iterator>(simple);
	}
}
