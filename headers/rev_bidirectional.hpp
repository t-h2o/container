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

	reference operator*(void);

	/* ++_self */
	_self &operator++(void);
	_self &operator--(void);

	/* _self++ */
	_self operator++(int);
	_self operator--(int);

	bool operator!=(_self const &other);

  private:
	iterator_type _it;
};

#include "../templates/rev_bidirectional.cpp"

} /* Namespace */

#endif /* REV_BIDIRECTIONAL_HPP */
