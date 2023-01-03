#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace ft
{

template <typename T> class iterator
{
  public:
	iterator(void);
	iterator(T *, size_t);

	T			&operator*(void);
	T			&operator[](size_t);
	iterator<T> &operator++(void);
	iterator<T>	 operator++(int);
	iterator<T> &operator--(void);
	iterator<T>	 operator--(int);
	iterator<T> &operator+(const long);
	iterator<T>	 operator-(const long);
	iterator<T> &operator+=(const long);
	iterator<T> &operator-=(const long);

	std::ptrdiff_t operator-(iterator const &);

	bool operator==(iterator<T> const &other);
	bool operator!=(iterator<T> const &other);
	bool operator>(iterator<T> const &other);
	bool operator<(iterator<T> const &other);
	bool operator>=(iterator<T> const &other);
	bool operator<=(iterator<T> const &other);

  private:
	T	  *_pointer;
	size_t _position;
};

#include "../templates/Iterator.cpp"

} /* namespace ft */

#endif /* ITERATOR_HPP */
