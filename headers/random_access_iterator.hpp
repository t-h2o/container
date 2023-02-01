#ifndef RANDOM_ACCESS_ITERATOR
#define RANDOM_ACCESS_ITERATOR

namespace ft
{

template <typename T>
class random_access_iterator : public ft::iterator_traits<ft::iterator<ft::random_access_iterator_tag, T> >
{
	typedef typename iterator<ft::random_access_iterator_tag, T>::iterator_category iterator_category;
	typedef typename iterator<ft::random_access_iterator_tag, T>::value_type		value_type;
	typedef typename iterator<ft::random_access_iterator_tag, T>::difference_type	difference_type;
	typedef typename iterator<ft::random_access_iterator_tag, T>::pointer			pointer;
	typedef typename iterator<ft::random_access_iterator_tag, T>::reference			reference;

  public:
	random_access_iterator(void);
	random_access_iterator(pointer, size_t);

	reference				operator*(void);
	reference				operator[](size_t);
	random_access_iterator &operator++(void);
	random_access_iterator	operator++(int);
	random_access_iterator &operator--(void);
	random_access_iterator	operator--(int);
	random_access_iterator	operator+(const long);
	random_access_iterator	operator-(const long);
	random_access_iterator &operator+=(const long);
	random_access_iterator &operator-=(const long);

	difference_type operator-(random_access_iterator const &);

	bool operator==(random_access_iterator const &other);
	bool operator!=(random_access_iterator const &other);
	bool operator>(random_access_iterator const &other);
	bool operator<(random_access_iterator const &other);
	bool operator>=(random_access_iterator const &other);
	bool operator<=(random_access_iterator const &other);

  private:
	pointer _pointer;
	size_t	_position;
};

#include "../templates/random_access_iterator.cpp"

}

#endif /* RANDOM_ACCESS_ITERATOR */
