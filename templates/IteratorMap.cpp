template <typename T1, typename T2> map<T1, T2>::iterator::iterator(void) : _actual(0) {}

template <typename T1, typename T2> map<T1, T2>::iterator::iterator(Node *node) : _actual(node) {}

template <typename T1, typename T2>
typename map<T1, T2>::pair &
map<T1, T2>::iterator::operator*(void)
{
	return _actual->dual;
}
