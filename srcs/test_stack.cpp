#include "Awesome.hpp"
#include "Iterator.hpp"
#include "Stack.hpp"
#include "color.hpp"
#include <gtest/gtest.h>
#include <iostream>
#include <stack>

template <typename T>
static void
scenario_one(void)
{
	ft::stack<T> asdf;

	asdf.push(42);

	std::cout << "top: " << asdf.top() << std::endl;
	std::cout << "size: " << asdf.size() << std::endl;

	asdf.push(422);

	std::cout << "top: " << asdf.top() << std::endl;
	std::cout << "size: " << asdf.size() << std::endl;
}

void
test_stack(void)
{
	title("Scenario 1: int");
	scenario_one<int>();
	title("Scenario 1: Awesome");
	scenario_one<Awesome>();
}
