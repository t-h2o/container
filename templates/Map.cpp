template <typename T1, typename T2> map<T1, T2>::map(void) : _root(0), _size(0)
{
}

template <typename T1, typename T2> map<T1, T2>::~map(void) { _free_tree(); }

/**
 * Capacity
 */

template <typename T1, typename T2>
bool
map<T1, T2>::empty(void) const
{
	return !_size;
}

template <typename T1, typename T2>
pair<T1, T2> &
map<T1, T2>::operator[](const T1 &key)
{
	t_node *ptr;

	ptr = _root;
	while (ptr && ptr->next)
	{
		ptr = ptr->next;
	}

	if (ptr)
	{
		ptr->next = new t_node;
		ptr = ptr->next;
	}
	else
	{
		ptr = new t_node;
		_root = ptr;
	}
	++_size;

	ptr->next = 0;
	ptr->dual.first = key;
	return ptr->dual;
}

template <typename T1, typename T2>
void
map<T1, T2>::_free_tree(void)
{
	t_node *ptr;
	t_node *free;

	ptr = _root;
	while (ptr)
	{
		free = ptr;
		ptr = ptr->next;
		delete free;
	}
}

template <typename T1, typename T2>
void
map<T1, T2>::print(void) const
{
	t_node *ptr(_root);

	std::cout << "map: size = " << _size << std::endl;

	while (ptr)
	{
		std::cout << ptr->dual;
		ptr = ptr->next;
	}
}
