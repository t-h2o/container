#include "algorithm.hpp"
#include "vector.hpp"
#include <algorithm>
#include <string>

#include "Tdd.hpp"

void
test_algorithm(void)
{
	{
		ft::vector<int> vec_ft1(5, 12);
		ft::vector<int> vec_ft2(6, 11);

		bool comp_ft
			= ft::lexicographical_compare(vec_ft1.begin(), vec_ft1.end(), vec_ft2.begin(), vec_ft2.end());
		bool comp_std
			= std::lexicographical_compare(vec_ft1.begin(), vec_ft1.end(), vec_ft2.begin(), vec_ft2.end());

		Tdd::expected(comp_ft, comp_std, "lexicographical compare");
	}
	{
		ft::vector<int> vec_ft1(5, 12);
		ft::vector<int> vec_ft2(6, 12);

		bool comp_ft
			= ft::lexicographical_compare(vec_ft1.begin(), vec_ft1.end(), vec_ft2.begin(), vec_ft2.end());
		bool comp_std
			= std::lexicographical_compare(vec_ft1.begin(), vec_ft1.end(), vec_ft2.begin(), vec_ft2.end());

		Tdd::expected(comp_ft, comp_std, "lexicographical compare");
	}
	{
		ft::vector<int> vec_ft1(6, 12);
		ft::vector<int> vec_ft2(5, 12);

		bool comp_ft
			= ft::lexicographical_compare(vec_ft1.begin(), vec_ft1.end(), vec_ft2.begin(), vec_ft2.end());
		bool comp_std
			= std::lexicographical_compare(vec_ft1.begin(), vec_ft1.end(), vec_ft2.begin(), vec_ft2.end());

		Tdd::expected(comp_ft, comp_std, "lexicographical compare");
	}
	{
		ft::vector<int> vec_ft1(6, 12);
		ft::vector<int> vec_ft2(6, 12);

		bool comp_ft
			= ft::lexicographical_compare(vec_ft1.begin(), vec_ft1.end(), vec_ft2.begin(), vec_ft2.end());
		bool comp_std
			= std::lexicographical_compare(vec_ft1.begin(), vec_ft1.end(), vec_ft2.begin(), vec_ft2.end());

		Tdd::expected(comp_ft, comp_std, "lexicographical compare");
	}
	{
		ft::vector<int> vec_ft1(6, 12);
		ft::vector<int> vec_ft2(6, 12);

		vec_ft1[5] = 11;

		bool comp_ft
			= ft::lexicographical_compare(vec_ft1.begin(), vec_ft1.end(), vec_ft2.begin(), vec_ft2.end());
		bool comp_std
			= std::lexicographical_compare(vec_ft1.begin(), vec_ft1.end(), vec_ft2.begin(), vec_ft2.end());

		Tdd::expected(comp_ft, comp_std, "lexicographical compare");
	}
	{
		ft::vector<int> vec_ft1(6, 12);
		ft::vector<int> vec_ft2(6, 12);

		vec_ft1[5] = 13;

		bool comp_ft
			= ft::lexicographical_compare(vec_ft1.begin(), vec_ft1.end(), vec_ft2.begin(), vec_ft2.end());
		bool comp_std
			= std::lexicographical_compare(vec_ft1.begin(), vec_ft1.end(), vec_ft2.begin(), vec_ft2.end());

		Tdd::expected(comp_ft, comp_std, "lexicographical compare");
	}
	{
		ft::vector<std::string> vec_ft1(6, "Hey");
		ft::vector<std::string> vec_ft2(6, "Hey");

		bool comp_ft
			= ft::lexicographical_compare(vec_ft1.begin(), vec_ft1.end(), vec_ft2.begin(), vec_ft2.end());
		bool comp_std
			= std::lexicographical_compare(vec_ft1.begin(), vec_ft1.end(), vec_ft2.begin(), vec_ft2.end());

		Tdd::expected(comp_ft, comp_std, "lexicographical compare");
	}
	{
		ft::vector<int> vec_ft1(6, 12);
		ft::vector<int> vec_ft2;

		bool comp_ft
			= ft::lexicographical_compare(vec_ft1.begin(), vec_ft1.end(), vec_ft2.begin(), vec_ft2.end());
		bool comp_std
			= std::lexicographical_compare(vec_ft1.begin(), vec_ft1.end(), vec_ft2.begin(), vec_ft2.end());

		Tdd::expected(comp_ft, comp_std, "lexicographical compare");
	}
	{
		ft::vector<int> vec_ft1;
		ft::vector<int> vec_ft2(6, 12);

		bool comp_ft
			= ft::lexicographical_compare(vec_ft1.begin(), vec_ft1.end(), vec_ft2.begin(), vec_ft2.end());
		bool comp_std
			= std::lexicographical_compare(vec_ft1.begin(), vec_ft1.end(), vec_ft2.begin(), vec_ft2.end());

		Tdd::expected(comp_ft, comp_std, "lexicographical compare");
	}
}
