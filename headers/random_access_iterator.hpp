#ifndef RANDOM_ACCESS_ITERATOR
#define RANDOM_ACCESS_ITERATOR

namespace ft
{

template <typename T> class random_access_iterator : public iterator<random_access_iterator_tag, T>
{
  public:
	random_access_iterator(void);
	random_access_iterator(T *, size_t);

	T					   &operator*(void);
	T					   &operator[](size_t);
	random_access_iterator &operator++(void);
	random_access_iterator	operator++(int);
	random_access_iterator &operator--(void);
	random_access_iterator	operator--(int);
	random_access_iterator	operator+(const long);
	random_access_iterator	operator-(const long);
	random_access_iterator &operator+=(const long);
	random_access_iterator &operator-=(const long);

	std::ptrdiff_t operator-(random_access_iterator const &);

	bool operator==(random_access_iterator const &other);
	bool operator!=(random_access_iterator const &other);
	bool operator>(random_access_iterator const &other);
	bool operator<(random_access_iterator const &other);
	bool operator>=(random_access_iterator const &other);
	bool operator<=(random_access_iterator const &other);

  private:
	T	  *_pointer;
	size_t _position;
};

#include "../templates/random_access_iterator.cpp"

}

#endif /* RANDOM_ACCESS_ITERATOR */
