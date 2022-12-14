template <typename T>
Vector<T>::Vector(void) : _size(0), _list(0)
{
	message("Vector: default constructor");
}

template <typename T>
Vector<T>::~Vector(void)
{
	message("Vector: destructor");

	delete [] this->_list;
}

template <typename T>
void	Vector<T>::assign(unsigned int nElements, T value)
{
	message("Vector: assign");

	delete [] this->_list;

	this->_size = nElements;
	this->_list = new T[nElements];

	for (unsigned int i = 0; i < nElements; i++)
		this->_list[i] = value;
}

template <typename T>
unsigned int	Vector<T>::size(void) const
{
	return this->_size;
}

template <typename T>
std::ostream	&operator<<(std::ostream &output, Vector<T> const &)
{
	output << "Vector: operator <<" << std::endl;
	return output;
}
