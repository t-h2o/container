#ifndef PAIR_HPP
#define PAIR_HPP

#include <iostream>

namespace ft
{

template <typename T1, typename T2> class pair
{
  public:
	/* Member Funcion */
	pair(void);
	pair(const pair &);
	pair(T1 const &, const T2 &);

	pair &operator=(const pair &);
	pair &operator=(const T2 &);

	T1	  first;
	T2	  second;
};

/* Extra... */
template <typename T1, typename T2>
std::ostream &operator<<(std::ostream &output, pair<T1, T2> const &);

#include "../templates/Pair.cpp"

} /* namespace ft */

#endif /* PAIR_HPP */
