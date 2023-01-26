template <typename T1, typename T2> map<T1, T2>::iterator::iterator(void) : _actual(0) {}

template <typename T1, typename T2> map<T1, T2>::iterator::iterator(Node *node) : _actual(node) {}

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
