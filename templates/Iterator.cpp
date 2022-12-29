template <typename T> Iterator<T>::Iterator(void) : _pointer(0), _position(0)
{
}

template <typename T>
Iterator<T>::Iterator(T *pointer, size_t position)
	: _pointer(pointer), _position(position)
{
}

template <typename T>
T &
Iterator<T>::operator*(void)
{
	return this->_pointer[_position];
}

template <typename T>
T &
Iterator<T>::operator[](size_t position)
{
	return this->_pointer[_position + position];
}

template <typename T>
Iterator<T> &
Iterator<T>::operator++(void)
{
	this->_pointer++;
	return *this;
}

template <typename T>
Iterator<T>
Iterator<T>::operator++(int)
{
	Iterator<T> prev;

	prev = *this;
	this->_pointer++;
	return prev;
}
