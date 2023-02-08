#include "Awesome.hpp"
#include "Tdd.hpp"
#include "color.hpp"
#include "test.hpp"

#include "chain_list.hpp"

template <typename T>
static void
test_it(ft::chain_list<T> &a)
{
	typename ft::chain_list<T>::iterator it(a.begin());

	while (it != a.end())
		std::cout << "iterator ++:  " << *it++ << std::endl;

	--it;
	while (it != a.end())
		std::cout << "iterator --:  " << *it-- << std::endl;

	typename ft::chain_list<T>::reverse_iterator rev_it(a.rbegin());

	while (rev_it != a.rend())
		std::cout << "reverse iterator ++:  " << *rev_it++ << std::endl;

	--rev_it;
	while (rev_it != a.rend())
		std::cout << "reverse iterator --:  " << *rev_it-- << std::endl;
}

template <typename T>
static void
test_put(ft::chain_list<T> &a, const T &item)
{
	a.put(item);
	std::cout << "size: " << a.size() << std::endl;
	a.last();
	test_it(a);
	std::cout << std::endl;
}

template <typename T>
static void
test(void)
{
	ft::chain_list<T> a;

	std::cout << "size: " << a.size() << std::endl;
	a.last();
	test_it(a);
	std::cout << std::endl;

	test_put<T>(a, 42);
	test_put<T>(a, 50);
	test_put<T>(a, 60);
	test_put<T>(a, 70);

	{
		typename ft::chain_list<T>::iterator it(a.begin());

		std::cout << "iterator begin: *it    : " << *it << std::endl;
		std::cout << "iterator begin: *(it++): " << *(it++) << std::endl;
		std::cout << "iterator begin: *it    : " << *it << std::endl;
		std::cout << "iterator begin: *(it--): " << *(it--) << std::endl;
		std::cout << "iterator begin: *it    : " << *it << std::endl;
		std::cout << "iterator begin: *(++it): " << *(++it) << std::endl;
		std::cout << "iterator begin: *it    : " << *it << std::endl;
		std::cout << "iterator begin: *(--it): " << *(--it) << std::endl;
		std::cout << "iterator begin: *it    : " << *it << std::endl << std::endl;
	}

	{
		typename ft::chain_list<T>::const_iterator it(a.cbegin());

		std::cout << "const iterator begin: *it    : " << *it << std::endl;
		std::cout << "const iterator begin: *(it++): " << *(it++) << std::endl;
		std::cout << "const iterator begin: *it    : " << *it << std::endl;
		std::cout << "const iterator begin: *(it--): " << *(it--) << std::endl;
		std::cout << "const iterator begin: *it    : " << *it << std::endl;
		std::cout << "const iterator begin: *(++it): " << *(++it) << std::endl;
		std::cout << "const iterator begin: *it    : " << *it << std::endl;
		std::cout << "const iterator begin: *(--it): " << *(--it) << std::endl;
		std::cout << "const iterator begin: *it    : " << *it << std::endl << std::endl;
	}

	{
		typename ft::chain_list<T>::reverse_iterator it(a.rbegin());

		std::cout << "reverse iterator begin: *it    : " << *it << std::endl;
		std::cout << "reverse iterator begin: *(it++): " << *(it++) << std::endl;
		std::cout << "reverse iterator begin: *it    : " << *it << std::endl;
		std::cout << "reverse iterator begin: *(it--): " << *(it--) << std::endl;
		std::cout << "reverse iterator begin: *it    : " << *it << std::endl;
		std::cout << "reverse iterator begin: *(++it): " << *(it++) << std::endl;
		std::cout << "reverse iterator begin: *it    : " << *it << std::endl;
		std::cout << "reverse iterator begin: *(--it): " << *(it--) << std::endl;
		std::cout << "reverse iterator begin: *it    : " << *it << std::endl << std::endl;
	}

	{
		typename ft::chain_list<T>::const_reverse_iterator it(a.crbegin());

		std::cout << "const reverse iterator begin: *it    : " << *it << std::endl;
		std::cout << "const reverse iterator begin: *(it++): " << *(it++) << std::endl;
		std::cout << "const reverse iterator begin: *it    : " << *it << std::endl;
		std::cout << "const reverse iterator begin: *(it--): " << *(it--) << std::endl;
		std::cout << "const reverse iterator begin: *it    : " << *it << std::endl;
		std::cout << "const reverse iterator begin: *(++it): " << *(it++) << std::endl;
		std::cout << "const reverse iterator begin: *it    : " << *it << std::endl;
		std::cout << "const reverse iterator begin: *(--it): " << *(it--) << std::endl;
		std::cout << "const reverse iterator begin: *it    : " << *it << std::endl;
	}
}

template <typename T>
static void
test_range(void)
{
	ft::chain_list<T> a;

	for (int i = 0; i < 100; i += 10)
		a.put(i);

	section("\tb(a.begin(), a.end())");
	{
		ft::chain_list<T> b(a.begin(), a.end());
		std::cout << "size: " << b.size() << std::endl;
	}

	section("\tb(a.cbegin(), a.cend())");
	{
		ft::chain_list<T> b(a.cbegin(), a.cend());
		std::cout << "size: " << b.size() << std::endl;
	}

	section("\tb(a.rbegin(), a.rend())");
	{
		ft::chain_list<T> b(a.rbegin(), a.rend());
		std::cout << "size: " << b.size() << std::endl;
	}

	section("\tb(a.crbegin(), a.crend())");
	{
		ft::chain_list<T> b(a.crbegin(), a.crend());
		std::cout << "size: " << b.size() << std::endl;
	}
}

void
test_chain_list(void)
{
	title("Chain list");

	section("test int");
	test<int>();

	section("test Awesome");
	test<Awesome>();

	section("test_range int");
	test_range<int>();
}
