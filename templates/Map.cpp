template <typename T1, typename T2> map<T1, T2>::map(void) : _root(0) {}

template <typename T1, typename T2> map<T1, T2>::~map(void) { delete _root; }

template <typename T1, typename T2>
pair<T1, T2> &
map<T1, T2>::operator[](const T1 &key)
{
	_root = new t_node;

	_root->dual.first = key;
	return _root->dual;
}
