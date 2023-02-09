#ifndef RANDOM_ACCESS_ITERATOR
#define RANDOM_ACCESS_ITERATOR

namespace ft
{

template <typename _Iter> class random_access_iterator
{
	typedef _Iter iterator_type;

	typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
	typedef typename iterator_traits<iterator_type>::value_type		   value_type;
	typedef typename iterator_traits<iterator_type>::difference_type   difference_type;
	typedef typename iterator_traits<iterator_type>::pointer		   pointer;
	typedef typename iterator_traits<iterator_type>::reference		   reference;

  public:
	random_access_iterator(void);
	random_access_iterator(pointer);
	template <typename _It> random_access_iterator(random_access_iterator<_It> const &);
	template <typename _It> random_access_iterator &operator=(random_access_iterator<_It> const &);

	pointer base(void) const;

	/* bidirectional */

	reference operator*(void);
	pointer	  operator->(void);

	bool operator==(random_access_iterator const &other);
	bool operator!=(random_access_iterator const &other);

	random_access_iterator &operator++(void);
	random_access_iterator &operator--(void);
	random_access_iterator	operator++(int);
	random_access_iterator	operator--(int);

	/* random_access_iterator */

	reference operator[](size_t);

	random_access_iterator	operator+(difference_type);
	random_access_iterator	operator-(difference_type);
	random_access_iterator &operator+=(difference_type);
	random_access_iterator &operator-=(difference_type);

	difference_type operator-(random_access_iterator const &);

	bool operator>(random_access_iterator const &other);
	bool operator<(random_access_iterator const &other);
	bool operator>=(random_access_iterator const &other);
	bool operator<=(random_access_iterator const &other);

  private:
	pointer _pointer;
};

#include "../templates/random_access_iterator.cpp"

}

#endif /* RANDOM_ACCESS_ITERATOR */
