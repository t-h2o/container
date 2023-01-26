template <typename T1, typename T2> map<T1, T2>::iterator::iterator(Node *end) : _actual(end), _end(end) {}

template <typename T1, typename T2>
map<T1, T2>::iterator::iterator(Node *node, Node *end) : _actual(node), _end(end)
{
}

template <typename T1, typename T2>
typename map<T1, T2>::pair &
map<T1, T2>::iterator::operator*(void)
{
	return _actual->dual;
}

template <typename T1, typename T2>
typename map<T1, T2>::iterator &
map<T1, T2>::iterator::operator++(void)
{
	if (_actual->key() == _bigger(_actual)->key())
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

template <typename T1, typename T2>
bool
map<T1, T2>::iterator::operator!=(iterator const &other) const
{
	return !(this->_actual == other._actual);
}

/**
 * Private
 */

template <typename T1, typename T2>
typename map<T1, T2>::Node *
map<T1, T2>::iterator::_bigger(Node *big) const
{
	while (big->parent)
		big = big->parent;

	while (big->right())
		big = big->right();

	return big;
}
