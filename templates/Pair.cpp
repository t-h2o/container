template <typename T1, typename T2> pair<T1, T2>::pair(void) {}

template <typename T1, typename T2>
pair<T1, T2>::pair(const pair &other)
	: _first(other._first), _second(other._second)
{
}

template <typename T1, typename T2>
pair<T1, T2>::pair(T1 const &first, T2 const &second)
	: _first(first), _second(second)
{
}

template <typename T1, typename T2>
pair<T1, T2> &
pair<T1, T2>::operator=(pair const &other)
{
	if (this == &other)
		return *this;

	this->_first = other._first;
	this->_second = other._second;

	return *this;
}
