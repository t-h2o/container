_node_base::_node_base(void) : next(0) {}

template <typename _Val> _node<_Val>::_node(const _Val &item) : _node_base(), value_field(item) {}

template <typename T, typename Alloc> chain_list<T, Alloc>::chain_list(void) : _start(0), _alloc_node() {}
template <typename T, typename Alloc> chain_list<T, Alloc>::~chain_list(void)
{
	_alloc_node.deallocate(_start, 1);
}

template <typename T, typename Alloc>
void
chain_list<T, Alloc>::put(const_reference item)
{
	std::cout << "Put: " << item << std::endl;
	_start = _alloc_node.allocate(1);
	_alloc_node.construct(_start, item);
}

template <typename T, typename Alloc>
void
chain_list<T, Alloc>::last(void)
{
	std::cout << "last: " << _start->_last_node(_start) << std::endl;
}
