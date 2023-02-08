#ifndef CHAIN_LIST_HPP
#define CHAIN_LIST_HPP

#include <Iterator.hpp>
#include <rev_bidirectional.hpp>

namespace ft
{

struct _node_base
{
	typedef _node_base		 *_Base_ptr;
	typedef const _node_base *_Const_Base_ptr;

	_node_base(void);

	_Base_ptr back;
	_Base_ptr next;
};

template <typename _Val> struct _node : _node_base
{
	_node(const _Val &);

	_Val *
	valptr(void)
	{
		return &value_field;
	}
	_Val value_field;
};

template <typename _Tp> struct _chain_list_iterator
{
	typedef _Tp	 value_type;
	typedef _Tp &reference;
	typedef _Tp *pointer;

	typedef _chain_list_iterator<_Tp> _self;
	typedef _node_base::_Base_ptr	  _Base_ptr;
	typedef _node<_Tp>				 *node_ptr;

	typedef bidirectional_iterator_tag iterator_category;
	typedef std::ptrdiff_t			   difference_type;

	_chain_list_iterator(_Base_ptr ptr) : _node_ptr(ptr) {}

	reference
	operator*(void) const
	{
		return *static_cast<node_ptr>(_node_ptr)->valptr();
	}

	pointer
	operator->(void) const
	{
		return static_cast<node_ptr>(_node_ptr)->valptr();
	}

	_self &
	operator++(void)
	{
		this->_node_ptr = this->_node_ptr->next;
		return *this;
	}

	_self
	operator++(int)
	{
		_self _tmp(*this);
		this->_node_ptr = this->_node_ptr->next;
		return _tmp;
	}

	_self &
	operator--(void)
	{
		this->_node_ptr = this->_node_ptr->back;
		return *this;
	}

	_self
	operator--(int)
	{
		_self _tmp(*this);
		this->_node_ptr = this->_node_ptr->back;
		return _tmp;
	}

	bool
	operator!=(_chain_list_iterator const &other)
	{
		return (this->_node_ptr != other._node_ptr);
	}

	_Base_ptr _node_ptr;
};

template <typename _Tp> struct _chain_list_const_iterator
{
	typedef _Tp		   value_type;
	typedef const _Tp &reference;
	typedef const _Tp *pointer;

	typedef _chain_list_iterator<_Tp> iterator;

	typedef _chain_list_const_iterator<_Tp> _self;
	typedef _node_base::_Const_Base_ptr		_Base_ptr;
	typedef const _node<_Tp>			   *node_ptr;

	typedef bidirectional_iterator_tag iterator_category;
	typedef std::ptrdiff_t			   difference_type;

	_chain_list_const_iterator(_Base_ptr ptr) : _node_ptr(ptr) {}

	reference
	operator*(void) const
	{
		return *const_cast<_node<_Tp> *>(static_cast<node_ptr>(_node_ptr))->valptr();
	}

	_self &
	operator++(void)
	{
		this->_node_ptr = this->_node_ptr->next;
		return *this;
	}

	_self
	operator++(int)
	{
		_self _tmp(*this);
		this->_node_ptr = this->_node_ptr->next;
		return _tmp;
	}

	_self &
	operator--(void)
	{
		this->_node_ptr = this->_node_ptr->back;
		return *this;
	}

	_self
	operator--(int)
	{
		_self _tmp(*this);
		this->_node_ptr = this->_node_ptr->back;
		return _tmp;
	}

	bool
	operator!=(_chain_list_const_iterator const &other)
	{
		return (this->_node_ptr != other._node_ptr);
	}

	_Base_ptr _node_ptr;
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

	node_ptr _last(void);

  public:
	typedef _chain_list_iterator<value_type>	   iterator;
	typedef _chain_list_const_iterator<value_type> const_iterator;

	typedef ft::rev_bidirectional<iterator>		  reverse_iterator;
	typedef ft::rev_bidirectional<const_iterator> const_reverse_iterator;

	chain_list(void);
	~chain_list(void);

	iterator begin(void);
	iterator end(void);

	const_iterator cbegin(void) const;
	const_iterator cend(void) const;

	reverse_iterator rbegin(void);
	reverse_iterator rend(void);

	const_reverse_iterator crbegin(void) const;
	const_reverse_iterator crend(void) const;

	void	  put(const_reference);
	void	  last(void);
	size_type size(void);

  private:
	node_ptr	   _start;
	node_ptr	   _end;
	node_allocator _alloc_node;
	size_type	   _size;
};

#include "../templates/chain_list.cpp"

} /* Namespace */

#endif /* CHAIN_LIST_HPP */
