#include "Awesome.hpp"
#include "Iterator.hpp"
#include "Tdd.hpp"
#include "color.hpp"
#include "stack.hpp"
#include <iostream>
#include <stack>

template <typename T>
static void
is_equal(ft::stack<T> &stack_ft, std::stack<T> &stack_std)
{
	Tdd::expected(stack_std.empty(), stack_ft.empty());
	Tdd::expected(stack_std.size(), stack_ft.size());
	Tdd::expected(stack_std.top(), stack_ft.top());
}

template <typename T>
static void
add_ten(ft::stack<T> &stack_ft, std::stack<T> &stack_std)
{
	for (int i = 0; i < 10; ++i)
	{
		stack_ft.push(static_cast<T>(i));
		stack_std.push(static_cast<T>(i));

		is_equal(stack_ft, stack_std);
	}
}

template <typename T>
static void
scenario_one(void)
{
	ft::stack<T>  stack_ft;
	std::stack<T> stack_std;

	add_ten(stack_ft, stack_std);

	stack_ft.push(42);
	stack_std.push(42);
	is_equal(stack_ft, stack_std);

	stack_ft.push(1234);
	stack_std.push(1234);
	is_equal(stack_ft, stack_std);

	{
		ft::stack<T>  ft_copy(stack_ft);
		std::stack<T> std_copy(stack_std);

		ft_copy.pop();
		std_copy.pop();
		is_equal(ft_copy, std_copy);
		is_equal(stack_ft, stack_std);

		ft_copy.pop();
		std_copy.pop();
		is_equal(ft_copy, std_copy);
		is_equal(stack_ft, stack_std);
	}

	stack_ft.pop();
	stack_std.pop();
	is_equal(stack_ft, stack_std);
}

void
test_stack(void)
{
	title("Scenario 1: int");
	scenario_one<int>();
	title("Scenario 1: Awesome");
	scenario_one<Awesome>();
}
