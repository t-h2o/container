#ifndef SIMPLE_STRING_ITERATOR_HPP
#define SIMPLE_STRING_ITERATOR_HPP

class SimpleStringIterator
{
  public:
	SimpleStringIterator(char *);

	char &operator*(void) const;

  private:
	char *_pointer;
};

#endif /* SIMPLE_STRING_ITERATOR_HPP */
