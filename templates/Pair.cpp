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

template <typename T1, typename T2>
void
pair<T1, T2>::swap(pair &other)
{
	T1 tmp1;
	T2 tmp2;

	tmp1 = this->_first;
	tmp2 = this->_second;

	this->_first = other._first;
	this->_second = other._second;

	other._first = tmp1;
	other._second = tmp2;
}
