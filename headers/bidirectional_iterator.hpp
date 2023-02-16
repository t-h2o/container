#ifndef BIDIRECTIONAL_ITERATOR
#define BIDIRECTIONAL_ITERATOR

#include "Iterator.hpp"
#include "node.hpp"

namespace ft
{

template <typename _Node> class bidirectional_iterator
{
	typedef _Node						  Node;
	typedef bidirectional_iterator<_Node> _self;
	typedef _self						 &_self_reference;

	typedef typename Node::TYPE value_type;

  public:
	bidirectional_iterator(void);
	bidirectional_iterator(Node **, Node *);
	bidirectional_iterator(Node **, Node *, Node *);

	_self_reference operator=(_self_reference);
	value_type	   &operator*(void);

	_self_reference operator++(void);
	_self_reference operator--(void);

	_self operator++(int);
	_self operator--(int);

	bool operator==(bidirectional_iterator const &) const;
	bool operator!=(bidirectional_iterator const &) const;

	Node *_bigger(Node *) const;

  private:
	Node **_root;
	Node  *_actual;
	Node  *_end;
};

#include "../templates/bidirectional_iterator.cpp"

} /* namespace ft */

#endif /* BIDIRECTIONAL_ITERATOR */
