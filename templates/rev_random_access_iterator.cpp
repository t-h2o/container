/* bidirectional */

template <typename _Iter>
typename rev_random_access_iterator<_Iter>::reference
rev_random_access_iterator<_Iter>::operator*(void)
{
	iterator_type _tmp(_it);
	return *--_tmp;
}

template <typename _Iter>
typename rev_random_access_iterator<_Iter>::pointer
rev_random_access_iterator<_Iter>::operator->(void)
{
	iterator_type _tmp(_it);
	--_tmp;
	return _tmp.operator->();
}

template <typename _Iter>
bool
rev_random_access_iterator<_Iter>::operator==(_self const &other)
{
	return _it == other._it;
}

template <typename _Iter>
bool
rev_random_access_iterator<_Iter>::operator!=(_self const &other)
{
	return _it != other._it;
}

template <typename _Iter>
typename rev_random_access_iterator<_Iter>::_self &
rev_random_access_iterator<_Iter>::operator++(void)
{
	--_it;
	return *this;
}

template <typename _Iter>
typename rev_random_access_iterator<_Iter>::_self &
rev_random_access_iterator<_Iter>::operator--(void)
{
	++_it;
	return *this;
}

template <typename _Iter>
typename rev_random_access_iterator<_Iter>::_self
rev_random_access_iterator<_Iter>::operator++(int)
{
	_self _tmp(*this);
	--_it;
	return _tmp;
}

template <typename _Iter>
typename rev_random_access_iterator<_Iter>::_self
rev_random_access_iterator<_Iter>::operator--(int)
{
	_self _tmp(*this);
	++_it;
	return _tmp;
}

/* random_access_iterator */

template <typename _Iter>
typename rev_random_access_iterator<_Iter>::reference
rev_random_access_iterator<_Iter>::operator[](size_t position)
{
	return _it[-position - 1];
}

template <typename _Iter>
typename rev_random_access_iterator<_Iter>::_self
rev_random_access_iterator<_Iter>::operator+(difference_type add)
{
	_self a(_it - add);
	return a;
}

template <typename _Iter>
typename rev_random_access_iterator<_Iter>::_self
rev_random_access_iterator<_Iter>::operator-(difference_type add)
{
	_self a(_it + add);
	return a;
}

template <typename _Iter>
typename rev_random_access_iterator<_Iter>::_self &
rev_random_access_iterator<_Iter>::operator+=(difference_type add)
{
	_it -= add;
	return *this;
}

template <typename _Iter>
typename rev_random_access_iterator<_Iter>::_self &
rev_random_access_iterator<_Iter>::operator-=(difference_type add)
{
	_it += add;
	return *this;
}

template <typename _Iter>
typename rev_random_access_iterator<_Iter>::difference_type
rev_random_access_iterator<_Iter>::operator-(_self const &other) const
{
	return other._it - _it;
}

template <typename _Iter>
bool
rev_random_access_iterator<_Iter>::operator>(const _self &other) const
{
	return (_it.base() < other._it.base());
}

template <typename _Iter>
bool
rev_random_access_iterator<_Iter>::operator<(const _self &other) const
{
	return (_it.base() > other._it.base());
}

template <typename _Iter>
bool
rev_random_access_iterator<_Iter>::operator>=(const _self &other) const
{
	return !(*this < other);
}

template <typename _Iter>
bool
rev_random_access_iterator<_Iter>::operator<=(const _self &other) const
{
	return !(*this > other);
}
