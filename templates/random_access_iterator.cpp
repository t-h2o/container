template <typename T> random_access_iterator<T>::random_access_iterator(void) : _pointer(0) {}

template <typename T> random_access_iterator<T>::random_access_iterator(pointer pointer) : _pointer(pointer)
{
}

template <typename T>
template <typename _It>
typename random_access_iterator<T>::random_access_iterator &
random_access_iterator<T>::operator=(const random_access_iterator<_It> &other)
{
	std::cout << "operator =" << std::endl;
	_pointer = other.base();
	return *this;
}

template <typename T>
template <typename _It>
random_access_iterator<T>::random_access_iterator(random_access_iterator<_It> const &other)
{
	std::cout << "copy conctructor" << std::endl;
	*this = other;
}

template <typename T>
typename random_access_iterator<T>::pointer
random_access_iterator<T>::base(void) const
{
	return _pointer;
}

template <typename T>
typename random_access_iterator<T>::reference
random_access_iterator<T>::operator*(void)
{
	return *_pointer;
}

template <typename T>
typename random_access_iterator<T>::reference
random_access_iterator<T>::operator[](size_t position)
{
	return _pointer[position];
}

template <typename T>
typename ft::random_access_iterator<T> &
random_access_iterator<T>::operator++(void)
{
	++_pointer;
	return *this;
}

template <typename T>
typename ft::random_access_iterator<T>
random_access_iterator<T>::operator++(int)
{
	random_access_iterator<T> prev;

	prev = *this;
	_pointer++;
	return prev;
}

template <typename T>
typename ft::random_access_iterator<T> &
random_access_iterator<T>::operator--(void)
{
	_pointer--;
	return *this;
}

template <typename T>
typename ft::random_access_iterator<T>
random_access_iterator<T>::operator--(int)
{
	random_access_iterator<T> prev;

	prev = *this;
	_pointer--;
	return prev;
}

template <typename T>
bool
random_access_iterator<T>::operator==(random_access_iterator<T> const &other)
{
	return _pointer == other._pointer;
}

template <typename T>
bool
random_access_iterator<T>::operator!=(random_access_iterator<T> const &other)
{
	return !(*this == other);
}

template <typename T>
bool
random_access_iterator<T>::operator>(random_access_iterator<T> const &other)
{
	return _pointer > other._pointer;
}

template <typename T>
bool
random_access_iterator<T>::operator<(random_access_iterator<T> const &other)
{
	return _pointer < other._pointer;
}

template <typename T>
bool
random_access_iterator<T>::operator>=(random_access_iterator<T> const &other)
{
	return (!(*this < other));
}

template <typename T>
bool
random_access_iterator<T>::operator<=(random_access_iterator<T> const &other)
{
	return (!(*this > other));
}

template <typename T>
typename ft::random_access_iterator<T>
random_access_iterator<T>::operator+(difference_type add)
{
	random_access_iterator<T> diff(_pointer + add);
	return diff;
}

template <typename T>
typename ft::random_access_iterator<T>
random_access_iterator<T>::operator-(difference_type remove)
{
	random_access_iterator<T> diff(_pointer - remove);
	return diff;
}

template <typename T>
typename random_access_iterator<T>::difference_type
random_access_iterator<T>::operator-(random_access_iterator const &other)
{
	return _pointer - other._pointer;
}

template <typename T>
typename ft::random_access_iterator<T> &
random_access_iterator<T>::operator+=(difference_type add)
{
	_pointer += add;
	return *this;
}

template <typename T>
typename ft::random_access_iterator<T> &
random_access_iterator<T>::operator-=(difference_type remove)
{
	_pointer -= remove;
	return *this;
}
