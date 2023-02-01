#ifndef RANDOM_ACCESS_ITERATOR
#define RANDOM_ACCESS_ITERATOR

namespace ft
{

class random_access_iterator : public iterator<random_access_iterator_tag, int>
{
  public:
	random_access_iterator(pointer);

  private:
	pointer _data;
};

#include "../templates/random_access_iterator.cpp"

}

#endif /* RANDOM_ACCESS_ITERATOR */
