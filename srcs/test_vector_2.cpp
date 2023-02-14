#include "Awesome.hpp"
#include "Iterator.hpp"
#include "Tdd.hpp"
#include "color.hpp"
#include "vector.hpp"
#include <iostream>
#include <vector>

template <typename TYPE>
static void
compare_reverse_iterator(std::vector<TYPE> &vec_std, ft::vector<TYPE> &vec_ft)
{
	typename std::vector<TYPE>::reverse_iterator it_std(vec_std.rbegin());
	typename ft::vector<TYPE>::reverse_iterator	 it_ft(vec_ft.rbegin());

	Tdd::expected(*it_ft, *it_std);

	for (size_t i = 0; i < vec_std.size(); ++i)
		Tdd::expected(it_ft[i], it_std[i]);

	Tdd::expected(vec_ft.rbegin() > vec_ft.rend(), vec_std.rbegin() > vec_std.rend());
	Tdd::expected(vec_ft.rbegin() < vec_ft.rend(), vec_std.rbegin() < vec_std.rend());
	Tdd::expected(vec_ft.rbegin() >= vec_ft.rend(), vec_std.rbegin() >= vec_std.rend());
	Tdd::expected(vec_ft.rbegin() <= vec_ft.rend(), vec_std.rbegin() <= vec_std.rend());

	Tdd::expected(vec_ft.rend() > vec_ft.rend(), vec_std.rend() > vec_std.rend());
	Tdd::expected(vec_ft.rend() < vec_ft.rend(), vec_std.rend() < vec_std.rend());
	Tdd::expected(vec_ft.rend() >= vec_ft.rend(), vec_std.rend() >= vec_std.rend());
	Tdd::expected(vec_ft.rend() <= vec_ft.rend(), vec_std.rend() <= vec_std.rend());

	if (vec_ft.size() < 3)
		return;

	it_ft = vec_ft.rbegin();
	it_std = vec_std.rbegin();
	Tdd::expected(*(it_ft++), *(it_std++));
	Tdd::expected(*(++it_ft), *(++it_std));
	Tdd::expected(*(it_ft--), *(it_std--));
	Tdd::expected(*(--it_ft), *(--it_std));

	it_ft += 1;
	it_std += 1;
	Tdd::expected(*(it_ft), *(it_std));

	it_ft = it_ft + 1;
	it_std = it_std + 1;
	Tdd::expected(*(it_ft), *(it_std));

	it_ft -= 1;
	it_std -= 1;
	Tdd::expected(*(it_ft), *(it_std));

	it_ft = it_ft - 1;
	it_std = it_std - 1;
	Tdd::expected(*(it_ft), *(it_std));
}

template <typename TYPE>
static void
compare_iterator(std::vector<TYPE> &vec_std, ft::vector<TYPE> &vec_ft)
{
	typename std::vector<TYPE>::iterator it_std(vec_std.begin());
	typename ft::vector<TYPE>::iterator	 it_ft(vec_ft.begin());

	Tdd::expected(*it_ft, *it_std);

	for (size_t i = 0; i < vec_std.size(); ++i)
		Tdd::expected(it_ft[i], it_std[i]);

	Tdd::expected(vec_ft.begin() > vec_ft.end(), vec_std.begin() > vec_std.end());
	Tdd::expected(vec_ft.begin() < vec_ft.end(), vec_std.begin() < vec_std.end());
	Tdd::expected(vec_ft.begin() >= vec_ft.end(), vec_std.begin() >= vec_std.end());
	Tdd::expected(vec_ft.begin() <= vec_ft.end(), vec_std.begin() <= vec_std.end());

	Tdd::expected(vec_ft.end() > vec_ft.end(), vec_std.end() > vec_std.end());
	Tdd::expected(vec_ft.end() < vec_ft.end(), vec_std.end() < vec_std.end());
	Tdd::expected(vec_ft.end() >= vec_ft.end(), vec_std.end() >= vec_std.end());
	Tdd::expected(vec_ft.end() <= vec_ft.end(), vec_std.end() <= vec_std.end());

	if (vec_ft.size() < 3)
		return;

	it_ft = vec_ft.begin();
	it_std = vec_std.begin();
	Tdd::expected(*(it_ft++), *(it_std++));
	Tdd::expected(*(++it_ft), *(++it_std));
	Tdd::expected(*(it_ft--), *(it_std--));
	Tdd::expected(*(--it_ft), *(--it_std));

	it_ft += 1;
	it_std += 1;
	Tdd::expected(*(it_ft), *(it_std));

	it_ft = it_ft + 1;
	it_std = it_std + 1;
	Tdd::expected(*(it_ft), *(it_std));

	it_ft -= 1;
	it_std -= 1;
	Tdd::expected(*(it_ft), *(it_std));

	it_ft = it_ft - 1;
	it_std = it_std - 1;
	Tdd::expected(*(it_ft), *(it_std));
}

template <typename TYPE>
static void
compare_vector(std::vector<TYPE> &vec_std, ft::vector<TYPE> &vec_ft)
{
	Tdd::expected(vec_ft.size(), vec_std.size());
	Tdd::expected(vec_ft.max_size(), vec_std.max_size());
	Tdd::expected(vec_ft.capacity(), vec_std.capacity());
	Tdd::expected(vec_ft.empty(), vec_std.empty());

	TYPE const *data_std = vec_std.data();
	TYPE const *data_ft = vec_ft.data();

	for (size_t i = 0; i < vec_std.size(); ++i)
		Tdd::expected(data_ft[i], data_std[i]);

	if (vec_ft.empty())
		return;

	compare_iterator<TYPE>(vec_std, vec_ft);
	compare_reverse_iterator<TYPE>(vec_std, vec_ft);
}

template <typename TYPE>
static void
test_push_back(std::vector<TYPE> &vec_std, ft::vector<TYPE> &vec_ft, TYPE number)
{
	vec_std.push_back(number);
	vec_ft.push_back(number);

	compare_vector(vec_std, vec_ft);
}

template <typename TYPE>
static void
start_test(void)
{
	std::vector<TYPE> vec_std;
	ft::vector<TYPE>  vec_ft;

	compare_vector(vec_std, vec_ft);

	void (*f[2])(std::vector<TYPE> &, ft::vector<TYPE> &, TYPE);
	f[0] = &test_push_back<TYPE>;
	f[0](vec_std, vec_ft, 0);
}

void
test_vector_2(void)
{
	title("test vector 2.0");

	start_test<int>();
	start_test<Awesome>();

	return;
}
