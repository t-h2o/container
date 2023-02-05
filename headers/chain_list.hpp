#ifndef CHAIN_LIST_HPP
#define CHAIN_LIST_HPP

namespace ft
{

struct _node_base
{
	typedef _node_base *_Base_ptr;

	_Base_ptr next;
};

template <typename _Val> struct _node : _node_base
{
	_Val value_field;
};

template <typename T, typename Alloc = std::allocator<T> > class chain_list
{
	typedef ft::_node<T> node;
	typedef node		*node_ptr;

  public:
	chain_list(void);

  private:
	node_ptr _start;
};

#include "../templates/chain_list.cpp"

}

#endif /* CHAIN_LIST_HPP */
