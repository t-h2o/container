#ifndef REV_BIDIRECTIONAL_HPP
#define REV_BIDIRECTIONAL_HPP

#include "Iterator.hpp"

namespace ft
{

template <typename _Iter>
class rev_bidirectional
	: public iterator<typename iterator_traits<_Iter>::iterator_category,
					  typename iterator_traits<_Iter>::value_type,
					  typename iterator_traits<_Iter>::difference_type,
					  typename iterator_traits<_Iter>::pointer, typename iterator_traits<_Iter>::reference>
{
	typedef _Iter iterator_type;

	typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
	typedef typename iterator_traits<iterator_type>::value_type		   value_type;
	typedef typename iterator_traits<iterator_type>::difference_type   difference_type;
	typedef typename iterator_traits<iterator_type>::pointer		   pointer;
	typedef typename iterator_traits<iterator_type>::reference		   reference;

	typedef rev_bidirectional<_Iter> _self;

  public:
	rev_bidirectional(void) : _it() {}
	rev_bidirectional(iterator_type it) : _it(it) {}
	template <typename _It> rev_bidirectional(rev_bidirectional<_It> const &other) { *this = other; }

	template <typename _It>
	rev_bidirectional &
	operator=(rev_bidirectional<_It> const &other)
	{
		_it = other._get_it();
		return *this;
	}

	/* bidirectional */

	reference operator*(void);
	pointer	  operator->(void);

	bool operator==(rev_bidirectional const &other);
	bool operator!=(rev_bidirectional const &other);

	_self &operator++(void);
	_self &operator--(void);
	_self  operator++(int);
	_self  operator--(int);

	iterator_type
	_get_it(void) const
	{
		return _it;
	}

  private:
	iterator_type _it;
};

#include "../templates/rev_bidirectional.cpp"

} /* Namespace */

#endif /* REV_BIDIRECTIONAL_HPP */
