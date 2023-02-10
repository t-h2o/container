#ifndef REV_RANDOM_ACCESS_ITERATOR_HPP
#define REV_RANDOM_ACCESS_ITERATOR_HPP

#include "Iterator.hpp"

namespace ft
{

template <typename _Iter>
class rev_random_access_iterator
	: public iterator<typename iterator_traits<_Iter>::iterator_category,
					  typename iterator_traits<_Iter>::value_type,
					  typename iterator_traits<_Iter>::difference_type,
					  typename iterator_traits<_Iter>::pointer, typename iterator_traits<_Iter>::reference>
{
	template <typename _It> friend class rev_random_access_iterator;
	typedef _Iter iterator_type;

	typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
	typedef typename iterator_traits<iterator_type>::value_type		   value_type;
	typedef typename iterator_traits<iterator_type>::difference_type   difference_type;
	typedef typename iterator_traits<iterator_type>::pointer		   pointer;
	typedef typename iterator_traits<iterator_type>::reference		   reference;

	typedef rev_random_access_iterator<_Iter> _self;

  public:
	rev_random_access_iterator(void) : _it() {}
	explicit rev_random_access_iterator(iterator_type it) : _it(it) {}
	rev_random_access_iterator(const rev_random_access_iterator &other) : _it(other._it) {}
	rev_random_access_iterator &
	operator=(const rev_random_access_iterator &other)
	{
		_it = other._it;
		return *this;
	}
	template <typename _It>
	rev_random_access_iterator(const rev_random_access_iterator<_It> &other) : _it(other._it)
	{
	}

	/* bidirectional */

	reference operator*(void);
	pointer	  operator->(void);

	bool operator==(rev_random_access_iterator const &other);
	bool operator!=(rev_random_access_iterator const &other);

	_self &operator++(void);
	_self &operator--(void);
	_self  operator++(int);
	_self  operator--(int);

	/* random_access_iterator */

	reference operator[](size_t);

	_self  operator+(difference_type);
	_self  operator-(difference_type);
	_self &operator+=(difference_type);
	_self &operator-=(difference_type);

	difference_type operator-(_self const &) const;

	bool operator>(const _self &other) const;
	bool operator<(const _self &other) const;
	bool operator>=(_self const &other) const;
	bool operator<=(_self const &other) const;

  private:
	iterator_type _it;
};

#include "../templates/rev_random_access_iterator.cpp"

} /* Namespace */

#endif /* REV_RANDOM_ACCESS_ITERATOR_HPP */
