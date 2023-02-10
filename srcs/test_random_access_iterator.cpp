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

template <typename _Iterator>
static void
test_iterator(NAME_SPACE::vector<t_simple> &simple)
{
	_Iterator it_end(simple.end());

	for (_Iterator it(simple.begin()); it != it_end; ++it)
		std::cout << ' ' << (*it).i;
	std::cout << std::endl;

	for (_Iterator it(simple.begin()); it != it_end; ++it)
		std::cout << ' ' << (*it).c;
	std::cout << std::endl;

	_Iterator it(simple.begin());
	for (int i = 0; i != it_end - it; ++i)
		std::cout << ' ' << it[i].c;
	std::cout << std::endl;
}

void
test_random_access_iterator(void)
{
	NAME_SPACE::vector<t_simple> simple;

	fill_simple(simple);

#ifdef STD
	title("Test: random access iterator with std");
#else
	title("Test: random access iterator with ft");
#endif

	{
		section("Test: iterator");
		typedef NAME_SPACE::vector<t_simple>::iterator iterator;

		test_iterator<iterator>(simple);
	}

	{
		section("Test: const_iterator");
		typedef NAME_SPACE::vector<t_simple>::const_iterator iterator;

		test_iterator<iterator>(simple);
	}
}
