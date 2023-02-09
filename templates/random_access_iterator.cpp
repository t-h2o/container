template <typename T> random_access_iterator<T>::random_access_iterator(void) : _pointer(0) {}

template <typename T> random_access_iterator<T>::random_access_iterator(pointer pointer) : _pointer(pointer)
{
}

template <typename T>
typename random_access_iterator<T>::reference
random_access_iterator<T>::operator*(void)
{
	return *this->_pointer;
}

template <typename T>
typename random_access_iterator<T>::reference
random_access_iterator<T>::operator[](size_t position)
{
	return this->_pointer[position];
}

template <typename T>
typename ft::random_access_iterator<T> &
random_access_iterator<T>::operator++(void)
{
	++this->_pointer;
	return *this;
}

template <typename T>
typename ft::random_access_iterator<T>
random_access_iterator<T>::operator++(int)
{
	random_access_iterator<T> prev;

	prev = *this;
	this->_pointer++;
	return prev;
}

template <typename T>
typename ft::random_access_iterator<T> &
random_access_iterator<T>::operator--(void)
{
	this->_pointer--;
	return *this;
}

template <typename T>
typename ft::random_access_iterator<T>
random_access_iterator<T>::operator--(int)
{
	random_access_iterator<T> prev;

	prev = *this;
	this->_pointer--;
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
	random_access_iterator<T> diff(this->_pointer + add);
	return diff;
}

template <typename T>
typename ft::random_access_iterator<T>
random_access_iterator<T>::operator-(difference_type remove)
{
	random_access_iterator<T> diff(this->_pointer - remove);
	return diff;
}

template <typename T>
typename random_access_iterator<T>::difference_type
random_access_iterator<T>::operator-(random_access_iterator const &other)
{
	return this->_pointer - other._pointer;
}

template <typename T>
typename ft::random_access_iterator<T> &
random_access_iterator<T>::operator+=(difference_type add)
{
	this->_pointer += add;
	return *this;
}

template <typename T>
typename ft::random_access_iterator<T> &
random_access_iterator<T>::operator-=(difference_type remove)
{
	this->_pointer -= remove;
	return *this;
}
