/* bidirectional */

template <typename _Iter>
typename rev_bidirectional<_Iter>::reference
rev_bidirectional<_Iter>::operator*(void)
{
	iterator_type _tmp(_it);
	return *--_tmp;
}

template <typename _Iter>
typename rev_bidirectional<_Iter>::pointer
rev_bidirectional<_Iter>::operator->(void)
{
	iterator_type _tmp(_it);
	--_tmp;
	return _tmp.operator->();
}

template <typename _Iter>
bool
rev_bidirectional<_Iter>::operator==(_self const &other)
{
	return _it == other._it;
}

template <typename _Iter>
bool
rev_bidirectional<_Iter>::operator!=(_self const &other)
{
	return _it != other._it;
}

template <typename _Iter>
typename rev_bidirectional<_Iter>::_self &
rev_bidirectional<_Iter>::operator++(void)
{
	--_it;
	return *this;
}

template <typename _Iter>
typename rev_bidirectional<_Iter>::_self &
rev_bidirectional<_Iter>::operator--(void)
{
	++_it;
	return *this;
}

template <typename _Iter>
typename rev_bidirectional<_Iter>::_self
rev_bidirectional<_Iter>::operator++(int)
{
	_self _tmp(*this);
	--_it;
	return _tmp;
}

template <typename _Iter>
typename rev_bidirectional<_Iter>::_self
rev_bidirectional<_Iter>::operator--(int)
{
	_self _tmp(*this);
	++_it;
	return _tmp;
}
