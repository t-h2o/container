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
		_actual = _actual->right();
	else if (_actual->get_side() == LEFT)
		_actual = _actual->parent;

	return *this;
}
