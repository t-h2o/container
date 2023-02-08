_node_base::_node_base(void) : back(0), next(0) {}

template <typename _Val> _node<_Val>::_node(const _Val &item) : _node_base(), value_field(item) {}

template <typename T, typename Alloc>
chain_list<T, Alloc>::chain_list(void) : _start(0), _alloc_node(), _size(0)
{
	_end = _alloc_node.allocate(1);
	_end->next = _end;
	_end->back = _end;
}

template <typename T, typename Alloc> chain_list<T, Alloc>::~chain_list(void)
{
	node_ptr ptr(_start);

	if (ptr == 0)
		return;

	while (ptr)
	{
		node_ptr parent(ptr);

		ptr = static_cast<node_ptr>(ptr->next);
		_alloc_node.destroy(parent);
		_alloc_node.deallocate(parent, 1);
	}
	_alloc_node.deallocate(_end, 1);
}

template <typename T, typename Alloc>
typename chain_list<T, Alloc>::iterator
chain_list<T, Alloc>::begin(void)
{
	return iterator(_start);
}

template <typename T, typename Alloc>
typename chain_list<T, Alloc>::const_iterator
chain_list<T, Alloc>::cbegin(void)
{
	return const_iterator(_start);
}

template <typename T, typename Alloc>
void
chain_list<T, Alloc>::put(const_reference item)
{
	std::cout << "Put: " << item << std::endl;

	node_ptr new_node = _alloc_node.allocate(1);
	_alloc_node.construct(new_node, item);
	if (_start == 0)
	{
		_start = new_node;
	}
	else
	{
		node_ptr last = (node_ptr)_start->_last_node(_start);
		new_node->back = last;
		last->next = new_node;
	}
	++_size;
}

template <typename T, typename Alloc>
void
chain_list<T, Alloc>::last(void)
{
	if (_start == 0)
	{
		std::cout << "last: no element" << std::endl;
		return;
	}

	std::cout << "last: " << static_cast<node_ptr>(_start->_last_node(_start))->value_field << std::endl;
}

template <typename T, typename Alloc>
typename chain_list<T, Alloc>::size_type
chain_list<T, Alloc>::size(void)
{
	return _size;
}
