#ifndef TEMPLATE_ITERATOR_HPP
#define TEMPLATE_ITERATOR_HPP

#include <iostream>

template <typename T> class TemplateIterator
{
  public:
	TemplateIterator(void);
	TemplateIterator(T *, size_t);

  private:
	T	  *_pointer;
	size_t _position;
};

#include "../templates/TemplateIterator.cpp"

#endif /* TEMPLATE_ITERATOR_HPP */
