_node_base::_node_base(void) : next(0) {}

template <typename _Val> _node<_Val>::_node(const _Val &item) : _node_base(), value_field(item) {}

template <typename T, typename Alloc> chain_list<T, Alloc>::chain_list(void) : _start(0), _alloc_node() {}

template <typename T, typename Alloc> chain_list<T, Alloc>::~chain_list(void)
{
	node_ptr ptr(_start);

	if (ptr == 0)
		return;

	while (ptr)
	{
		node_ptr parent(ptr);

		ptr = static_cast<node_ptr>(ptr->next);
		_alloc_node.deallocate(parent, 1);
	}
}

template <typename T, typename Alloc>
void
chain_list<T, Alloc>::put(const_reference item)
{
	std::cout << "Put: " << item << std::endl;

	if (_start == 0)
	{
		_start = _alloc_node.allocate(1);
		_alloc_node.construct(_start, item);
	}
	else
	{
		node_ptr last = (node_ptr)_start->_last_node(_start);
		last->next = _alloc_node.allocate(1);
		_alloc_node.construct((node_ptr)last->next, item);
	}
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
