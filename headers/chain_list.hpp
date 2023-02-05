#ifndef CHAIN_LIST_HPP
#define CHAIN_LIST_HPP

namespace ft
{

struct _node_base
{
	typedef _node_base *_Base_ptr;

	_node_base(void);

	_Base_ptr next;
};

template <typename _Val> struct _node : _node_base
{
	_node(const _Val &);

	_Val value_field;
};

template <typename T, typename Alloc = std::allocator<T> > class chain_list
{
	typedef ft::_node<T> node;
	typedef node		*node_ptr;

	typedef Alloc allocator_type;

	typedef typename allocator_type::value_type		 value_type;
	typedef typename allocator_type::pointer		 pointer;
	typedef typename allocator_type::reference		 reference;
	typedef typename allocator_type::const_pointer	 const_pointer;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::difference_type difference_type;
	typedef typename allocator_type::size_type		 size_type;

	typedef typename allocator_type::template rebind<node>::other node_allocator;

  public:
	chain_list(void);
	~chain_list(void);

	void put(const_reference);

  private:
	node_ptr	   _start;
	node_allocator _alloc_node;
};

#include "../templates/chain_list.cpp"

}

#endif /* CHAIN_LIST_HPP */
