#ifndef ALGORITHM_HPP
#define ALGORITHM_HPP

#include <iostream>

namespace ft
{

/** Lexicographical comparison is an operation with the following properties:
 * Two ranges are compared element by element.
 * The first mismatching element defines which range is lexicographically less or greater than the other.
 * If one range is a prefix of another, the shorter range is lexicographically less than the other.
 * If two ranges have equivalent elements and are of the same length, then the ranges are lexicographically
 * equal. An empty range is lexicographically less than any non-empty range. Two empty ranges are
 * lexicographically equal.
 *
 * Return value:
 * true if the first range is lexicographically less than the second, otherwise false.
 */
template <typename It1, typename It2>
bool
lexicographical_compare(It1 first1, It1 last1, It2 first2, It2 last2)
{
	while (first1 != last1 && first2 != last2 && *first1 == *first2)
	{
		++first1;
		++first2;
	}

	if (first1 == last1 && first2 != last2)
		return true;
	if (first2 == last2 && first1 != last1)
		return false;

	if (*first1 < *first2)
		return true;

	return false;
}
} /* namespace ft */

#endif /* ALGORITHM_HPP */
