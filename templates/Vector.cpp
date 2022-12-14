template <typename T>
Vector<T>::Vector(void)
{
	message("Vector: default constructor");
	this->_list = new T[0];
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

	this->_list = new T[nElements];

	for (unsigned int i = 0; i < nElements; i++)
		this->_list[i] = value;
}
