#ifndef TDD_HPP
#define TDD_HPP

#include <iostream>

class Tdd
{
  public:
	template <typename T> static void expected(T const &, T const &);
	template <typename T> static void expected(T const &, T const &, std::string const &);
};

#include "../templates/Tdd.cpp"

#endif /* TDD_HPP */
