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
  private:
	ft::_node<T> *start;
};

}

#endif /* CHAIN_LIST_HPP */
