template <typename T> random_access_iterator<T>::random_access_iterator(void) : _pointer(0), _position(0) {}

template <typename T>
random_access_iterator<T>::random_access_iterator(pointer pointer, size_t position)
	: _pointer(pointer), _position(position)
{
}

template <typename T>
typename random_access_iterator<T>::reference
random_access_iterator<T>::operator*(void)
{
	return this->_pointer[_position];
}

template <typename T>
typename random_access_iterator<T>::reference
random_access_iterator<T>::operator[](size_t position)
{
	return this->_pointer[_position + position];
}

template <typename T>
typename ft::random_access_iterator<T> &
random_access_iterator<T>::operator++(void)
{
	this->_position++;
	return *this;
}

template <typename T>
typename ft::random_access_iterator<T>
random_access_iterator<T>::operator++(int)
{
	random_access_iterator<T> prev;

	prev = *this;
	this->_position++;
	return prev;
}

template <typename T>
typename ft::random_access_iterator<T> &
random_access_iterator<T>::operator--(void)
{
	this->_position--;
	return *this;
}

template <typename T>
typename ft::random_access_iterator<T>
random_access_iterator<T>::operator--(int)
{
	random_access_iterator<T> prev;

	prev = *this;
	this->_position--;
	return prev;
}

template <typename T>
bool
random_access_iterator<T>::operator==(random_access_iterator<T> const &other)
{
	return (&(this->_pointer[this->_position]) == &(other._pointer[other._position]));
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
	return (&(this->_pointer[this->_position]) > &(other._pointer[other._position]));
}

template <typename T>
bool
random_access_iterator<T>::operator<(random_access_iterator<T> const &other)
{
	return (&(this->_pointer[this->_position]) < &(other._pointer[other._position]));
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
random_access_iterator<T>::operator+(const long add)
{
	random_access_iterator<T> diff(this->_pointer, this->_position + add);
	return diff;
}

template <typename T>
typename ft::random_access_iterator<T>
random_access_iterator<T>::operator-(const long remove)
{
	random_access_iterator<T> diff(this->_pointer, this->_position - remove);
	return diff;
}

template <typename T>
typename random_access_iterator<T>::difference_type
random_access_iterator<T>::operator-(random_access_iterator const &other)
{
	return this->_position - other._position;
}

template <typename T>
typename ft::random_access_iterator<T> &
random_access_iterator<T>::operator+=(const long add)
{
	this->_position += add;
	return *this;
}

template <typename T>
typename ft::random_access_iterator<T> &
random_access_iterator<T>::operator-=(const long remove)
{
	this->_position -= remove;
	return *this;
}
