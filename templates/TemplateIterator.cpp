template <typename T>
TemplateIterator<T>::TemplateIterator(void) : _pointer(0), _position(0)
{
}

template <typename T>
TemplateIterator<T>::TemplateIterator(T *pointer, size_t position)
	: _pointer(pointer), _position(position)
{
}

template <typename T>
T &
TemplateIterator<T>::operator*(void)
{
	return this->_pointer[_position];
}
