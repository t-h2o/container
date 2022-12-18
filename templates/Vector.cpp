template <typename T>
Vector<T>::Vector(void) : _list(0), _maxSize(0), _size(0)
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
	this->_maxSize = nElements;
	this->_list = new T[nElements];

	for (unsigned int i = 0; i < nElements; i++)
		this->_list[i] = value;
}

template <typename T>
T	&Vector<T>::operator[](unsigned int position) const
{
	return this->_list[position];
}

template <typename T>
T	&Vector<T>::front(void) const
{
	return this->_list[0];
}

template <typename T>
unsigned int	Vector<T>::size(void) const
{
	return this->_size;
}

template <typename T>
unsigned int	Vector<T>::max_size(void) const
{
	return this->_size;
}

template <typename T>
bool	Vector<T>::empty(void) const
{
	return this->_size;
}

template <typename T>
std::ostream	&operator<<(std::ostream &output, Vector<T> const & vec)
{
	output << "(vector) = size=" << vec.size() << " {" << std::endl;
	for (unsigned int i = 0; i < vec.size(); i++)
		output << "  ["<< i << "] = " << vec[i] << std::endl;
	output << "}" << std::endl;
	return output;
}
