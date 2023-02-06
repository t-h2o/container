#include "Awesome.hpp"
#include "Tdd.hpp"
#include "color.hpp"
#include "test.hpp"

#include "chain_list.hpp"

template <typename T>
static void
test(void)
{
	ft::chain_list<T> a;

	std::cout << "size: " << a.size() << std::endl;
	a.last();

	a.put(42);
	std::cout << "size: " << a.size() << std::endl;
	a.last();

	a.put(1234);
	std::cout << "size: " << a.size() << std::endl;
	a.last();

	{
		typename ft::chain_list<T>::iterator it(a.begin());

		std::cout << "iterator begin: *it    : " << *it << std::endl;
		std::cout << "iterator begin: *(it++): " << *(it++) << std::endl;
		std::cout << "iterator begin: *it    : " << *it << std::endl;
		std::cout << "iterator begin: *(it--): " << *(it--) << std::endl;
		std::cout << "iterator begin: *it    : " << *it << std::endl << std::endl;
	}

	{
		typename ft::chain_list<T>::iterator it(a.begin());

		std::cout << "iterator begin: *it    : " << *it << std::endl;
		std::cout << "iterator begin: *(++it): " << *(++it) << std::endl;
		std::cout << "iterator begin: *it    : " << *it << std::endl;
		std::cout << "iterator begin: *(--it): " << *(--it) << std::endl;
		std::cout << "iterator begin: *it    : " << *it << std::endl << std::endl;
	}

	{
		typename ft::chain_list<T>::const_iterator it(a.cbegin());

		std::cout << "iterator begin: *it    : " << *it << std::endl;
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
}
