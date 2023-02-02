#ifndef BIDIRECTIONAL_ITERATOR
#define BIDIRECTIONAL_ITERATOR

namespace ft
{

template <typename T>
class bidirectional_iterator : public ft::iterator_traits<ft::iterator<ft::bidirectional_iterator_tag, T> >
{
	typedef typename iterator<ft::bidirectional_iterator_tag, T>::iterator_category iterator_category;
	typedef typename iterator<ft::bidirectional_iterator_tag, T>::value_type		value_type;
	typedef typename iterator<ft::bidirectional_iterator_tag, T>::difference_type	difference_type;
	typedef typename iterator<ft::bidirectional_iterator_tag, T>::pointer			pointer;
	typedef typename iterator<ft::bidirectional_iterator_tag, T>::reference			reference;

  public:
	bidirectional_iterator(pointer);

  private:
	pointer _pointer;
};

#include "../templates/bidirectional_iterator.cpp"

} /* namespace ft */

#endif /* BIDIRECTIONAL_ITERATOR */
