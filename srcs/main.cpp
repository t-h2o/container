#include	<iostream>
#include	"color.hpp"
#include	"Vector.hpp"
#include	"Awesome.hpp"
#include	<vector>
#include	<gtest/gtest.h>

static void	test_awesome(void)
{
	section("Test with Awesome class");

	Awesome awesome;

	{
		Vector<Awesome>			vec_ft;
		vec_ft.assign(5, awesome);
		vec_ft.pop_back();

		Vector<Awesome>			vec_ft_copy;
		vec_ft[0].set_number(42);
		vec_ft[2].set_number(21);
		section("copy");
		vec_ft = vec_ft;
		vec_ft_copy = vec_ft;

		std::cout << "ft" << vec_ft;
		std::cout << "copy" << vec_ft_copy;
	}
}

static void	test_comparison(void)
{
	section("Test with comparison");

	std::vector<int>	vec_std;
	Vector<int>			vec_ft;

	EXPECT_EQ(vec_ft.size(), vec_std.size());
	EXPECT_EQ(vec_ft.max_size(), vec_std.max_size());
	EXPECT_EQ(vec_ft.empty(), vec_std.empty());

	vec_ft.assign(7, 100);
	vec_std.assign(7, 100);

	EXPECT_EQ(vec_ft[0], vec_std[0]);
	EXPECT_EQ(vec_ft[6], vec_std[6]);
	EXPECT_EQ(vec_ft.size(), vec_std.size());
	EXPECT_EQ(vec_ft.max_size(), vec_std.max_size());
	EXPECT_EQ(vec_ft.empty(), vec_std.empty());

	vec_ft.pop_back();
	vec_std.pop_back();

	EXPECT_EQ(vec_ft.size(), vec_std.size());
	EXPECT_EQ(vec_ft.max_size(), vec_std.max_size());
	EXPECT_EQ(vec_ft.empty(), vec_std.empty());

	vec_ft.push_back(12);
	vec_std.push_back(12);

	EXPECT_EQ(vec_ft.size(), vec_std.size());
	EXPECT_EQ(vec_ft.max_size(), vec_std.max_size());
	EXPECT_EQ(vec_ft.empty(), vec_std.empty());

	vec_ft.push_back(13);
	vec_std.push_back(13);

	EXPECT_EQ(vec_ft.size(), vec_std.size());
	EXPECT_EQ(vec_ft.max_size(), vec_std.max_size());
	EXPECT_EQ(vec_ft.empty(), vec_std.empty());

	vec_ft.clear();
	vec_std.clear();

	EXPECT_EQ(vec_ft.size(), vec_std.size());
	EXPECT_EQ(vec_ft.max_size(), vec_std.max_size());
	EXPECT_EQ(vec_ft.empty(), vec_std.empty());

	vec_ft.push_back(13);
	vec_std.push_back(13);

	EXPECT_EQ(vec_ft.size(), vec_std.size());
	EXPECT_EQ(vec_ft.max_size(), vec_std.max_size());
	EXPECT_EQ(vec_ft.empty(), vec_std.empty());
}

static void	test_my_vector(void)
{
	Vector<int>	vec;

	section("assign 7 times the value 100");
	vec.assign(7, 100);

	section("print vec");
	std::cout << vec << std::endl;

	section("add 1, 2, 3...");
	for (unsigned long i = 0; i < vec.size(); i++)
		vec[i] += i;

	section("print vec");
	std::cout << vec << std::endl;

	section("print the 3th number");
	std::cout << vec[3] << std::endl;

	section("print the front number");
	std::cout << vec.front() << std::endl;

	section("print the back number");
	std::cout << vec.back() << std::endl;

	section("pop back number");
	vec.pop_back();

	section("print vec");
	std::cout << vec << std::endl;

	section("print the back number");
	std::cout << vec.back() << std::endl;

	section("try an overrange number");
	try
	{
		std::cout << "vec at    2 : " << vec.at(2) << std::endl;
		std::cout << "vec at 1234 : " << vec.at(1234) << std::endl;
	}
	catch (std::exception &e)
	{
		print_exception(e);
	}

	section("print the max size");
	std::cout << vec.max_size() << std::endl;

	section("push back 42");
	int	myint = 42;
	vec.push_back(myint);

	section("print vec");
	std::cout << vec << std::endl;
}

static void	test_vector(void)
{
	std::vector<int>	vec;

	section("assign 7 times the value 100");
	vec.assign(11, 100);

	section("print the 3th number");
	std::cout << vec[3] << std::endl;
}

int	main(void)
{
	title("Main");

	test_my_vector();
	test_vector();
	test_comparison();
	test_awesome();

	return 0;
}
