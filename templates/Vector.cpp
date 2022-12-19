/**
 * Member Funcion
 */

template <typename T>
Vector<T>::Vector(void) : _list(0), _maxSize(0), _size(0), _allocated(0)
{
	message("Vector: default constructor");
}

template <typename T>
Vector<T>::~Vector(void)
{
	message("Vector: destructor");

	_allocator.deallocate(this->_list, this->_allocated);
}

/**
 * Capacity
 */

template <typename T>
unsigned int	Vector<T>::size(void) const
{
	return this->_size;
}

template <typename T>
unsigned int	Vector<T>::max_size(void) const
{
	return this->_allocator.max_size();
}

template <typename T>
bool	Vector<T>::empty(void) const
{
	return this->_size;
}

/**
 * Element access
 */

template <typename T>
T	&Vector<T>::operator[](unsigned int position) const
{
	return this->_list[position];
}

template <typename T>
T	&Vector<T>::at(unsigned int position) const
{
	if (this->size() <= position)
		throw out_of_range();
	return (*this)[position];
}

template <typename T>
T	&Vector<T>::front(void) const
{
	return this->_list[0];
}

template <typename T>
T	&Vector<T>::back(void) const
{
	return this->_list[this->_size - 1];
}

/**
 * Modifiers
 */

template <typename T>
void	Vector<T>::assign(unsigned int nElements, T value)
{
	message("Vector: assign");

	_allocator.deallocate(this->_list, this->_allocated);

	this->_size = nElements;
	this->_allocated = nElements;
	this->_maxSize = nElements;
	this->_list = _allocator.allocate(nElements);

	for (unsigned int i = 0; i < nElements; i++)
		this->_list[i] = value;
}

template <typename T>
void	Vector<T>::push_back(T & object)
{
	std::cout << object << std::endl;
	if (this->_allocated == this->_size)
	{
		std::cout << "need reallocation" << std::endl;
	}
	else
	{
		std::cout << "push back" << object << std::endl;
		this->_allocator.construct(&((*this)[this->_size]), object);
		++this->_size;
	}
}

template <typename T>
void	Vector<T>::pop_back(void)
{
	message("Vector: pop_back");

	if (this->empty() == 0)
		return ;

	--this->_size;
}

/**
 * Extra...
 */

template <typename T>
std::ostream	&operator<<(std::ostream &output, Vector<T> const & vec)
{
	output << "(vector) = size=" << vec.size() << " {" << std::endl;
	for (unsigned int i = 0; i < vec.size(); i++)
		output << "  ["<< i << "] = " << vec[i] << std::endl;
	output << "}" << std::endl;
	return output;
}
