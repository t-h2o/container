template <typename _Node, typename _Iter> bidirectional_iterator<_Node, _Iter>::bidirectional_iterator(void)
{
}

template <typename _Node, typename _Iter>
bidirectional_iterator<_Node, _Iter>::bidirectional_iterator(Node **root, Node *end)
	: _root(root), _actual(end), _end(end)
{
}

template <typename _Node, typename _Iter>
bidirectional_iterator<_Node, _Iter>::bidirectional_iterator(Node **root, Node *node, Node *end)
	: _root(root), _actual(node), _end(end)
{
}

template <typename _Node, typename _Iter>
typename bidirectional_iterator<_Node, _Iter>::_self_reference
bidirectional_iterator<_Node, _Iter>::operator=(_self_reference other)
{
	_root = other._root;
	_actual = other._actual;
	_end = other._end;
}

template <typename _Node, typename _Iter>
typename bidirectional_iterator<_Node, _Iter>::value_type &
bidirectional_iterator<_Node, _Iter>::operator*(void)
{
	return _actual->dual;
}

template <typename _Node, typename _Iter>
typename bidirectional_iterator<_Node, _Iter>::_self_reference
bidirectional_iterator<_Node, _Iter>::operator++(void)
{
	if (_actual->dual == _bigger(_actual)->dual)
	{
		_actual = _end;
		return *this;
	}
	if (_actual->parent == 0)
	{
		if (_actual->right())
		{
			_actual = _actual->right();
			while (_actual->left())
				_actual = _actual->left();
		}
	}
	else if (_actual->right())
	{
		if (_actual->right())
		{
			_actual = _actual->right();
			while (_actual->left())
				_actual = _actual->left();
		}
	}
	else if (_actual->get_side() == LEFT)
	{
		_actual = _actual->parent;
	}
	else if (_actual->get_side() == RIGHT)
	{
		while (_actual->parent && _actual->get_side() == RIGHT)
			_actual = _actual->parent;
		if (_actual->parent)
			_actual = _actual->parent;
	}

	return *this;
}

template <typename _Node, typename _Iter>
typename bidirectional_iterator<_Node, _Iter>::_self_reference
bidirectional_iterator<_Node, _Iter>::operator--(void)
{
	if (_actual->key() == _end->key())
	{
		_actual = _bigger(*_root);
		return *this;
	}
	if (_actual->parent == 0)
	{
		if (_actual->left())
		{
			_actual = _actual->left();
			while (_actual->right())
				_actual = _actual->right();
		}
	}
	else if (_actual->left())
	{
		if (_actual->left())
		{
			_actual = _actual->left();
			while (_actual->right())
				_actual = _actual->right();
		}
	}
	else if (_actual->get_side() == RIGHT)
	{
		_actual = _actual->parent;
	}
	else if (_actual->get_side() == LEFT)
	{
		while (_actual->parent && _actual->get_side() == LEFT)
			_actual = _actual->parent;
		if (_actual->parent)
			_actual = _actual->parent;
	}

	return *this;
}

template <typename _Node, typename _Iter>
typename bidirectional_iterator<_Node, _Iter>::_self
bidirectional_iterator<_Node, _Iter>::operator++(int)
{
	bidirectional_iterator ret(*this);

	++(*this);

	return ret;
}

template <typename _Node, typename _Iter>
typename bidirectional_iterator<_Node, _Iter>::_self
bidirectional_iterator<_Node, _Iter>::operator--(int)
{
	bidirectional_iterator ret(*this);

	--(*this);

	return ret;
}

template <typename _Node, typename _Iter>
bool
bidirectional_iterator<_Node, _Iter>::operator==(bidirectional_iterator const &other) const
{
	return this->_actual == other._actual;
}

template <typename _Node, typename _Iter>
bool
bidirectional_iterator<_Node, _Iter>::operator!=(bidirectional_iterator const &other) const
{
	return !(this->_actual == other._actual);
}

/**
 * Private
 */

template <typename _Node, typename _Iter>
typename bidirectional_iterator<_Node, _Iter>::Node *
bidirectional_iterator<_Node, _Iter>::_bigger(Node *big) const
{
	while (big->parent)
		big = big->parent;

	while (big->right())
		big = big->right();

	return big;
}
