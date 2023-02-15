#ifndef PAIR_HPP
#define PAIR_HPP

#include <iostream>

namespace ft
{

template <typename Key, typename Type> class pair
{
  public:
	/* Member Funcion */
	pair(void);
	pair(const pair &);
	pair(Key const &, const Type &);

	pair &operator=(const pair &);
	pair &operator=(const Type &);

	Key	 first;
	Type second;
};

template <typename Key, typename Value>
typename ft::pair<Key, Value>
make_pair(Key t, Value u)
{
	return pair<Key, Value>(t, u);
}

/* Extra... */
template <typename Key, typename Type>
std::ostream &operator<<(std::ostream &output, pair<Key, Type> const &);

#include "../templates/pair.cpp"

} /* namespace ft */

#endif /* PAIR_HPP */
