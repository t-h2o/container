#ifndef RANDOM_ACCESS_ITERATOR
#define RANDOM_ACCESS_ITERATOR

namespace ft
{

template <typename T> class random_access_iterator : public iterator<random_access_iterator_tag, T>
{
  public:
	random_access_iterator(T *);

  private:
	T *_data;
};

#include "../templates/random_access_iterator.cpp"

}

#endif /* RANDOM_ACCESS_ITERATOR */
