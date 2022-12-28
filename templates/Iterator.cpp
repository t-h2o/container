template <typename T> Iterator<T>::Iterator(void) : _pointer(0), _position(0)
{
}

template <typename T>
Iterator<T>::Iterator(T *pointer, size_t position)
	: _pointer(pointer), _position(position)
{
}
