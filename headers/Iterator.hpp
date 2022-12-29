#ifndef ITERATOR_HPP
#define ITERATOR_HPP

namespace ft
{
template <typename T> class Iterator
{
  public:
	Iterator(void);
	Iterator(T *, size_t);

	T			&operator*(void);
	T			&operator[](size_t);
	Iterator<T> &operator++(void);
	Iterator<T>	 operator++(int);

  private:
	T	  *_pointer;
	size_t _position;
};

#include "../templates/Iterator.cpp"
}

#endif /* ITERATOR_HPP */
