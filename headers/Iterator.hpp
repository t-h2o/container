#ifndef ITERATOR_HPP
#define ITERATOR_HPP

template <typename T> class Iterator
{
  public:
	Iterator(void);
	Iterator(T *, size_t);

	T &operator[](size_t);

  private:
	T	  *_pointer;
	size_t _position;
};

#include "../templates/Iterator.cpp"

#endif /* ITERATOR_HPP */
