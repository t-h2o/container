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

  private:
	T	  *_pointer;
	size_t _position;
};

#include "../templates/Iterator.cpp"
}

#endif /* ITERATOR_HPP */
