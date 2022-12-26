/**
 * Member Funcion
 */

template <typename T>
Vector<T>::Vector(void) : _list(0), _maxSize(0), _size(0), _allocated(0)
{
	message("Vector: default constructor");
}

template <typename T> Vector<T>::~Vector(void)
{
	message("Vector: destructor");

	this->clear();
}

template <typename T>
Vector<T> &
Vector<T>::operator=(Vector const &other)
{
	if (this == &other)
		return *this;

	this->clear();
	this->_list = this->_allocator.allocate(other._allocated);
	this->_size = other._size;
	this->_allocated = other._allocated;

	for (size_t i = 0; i < other._size; ++i)
	{
		this->_allocator.construct(&(*this)[i], other[i]);
	}

	return *this;
}

/**
 * Capacity
 */

template <typename T>
size_t
Vector<T>::size(void) const
{
	return this->_size;
}

template <typename T>
size_t
Vector<T>::max_size(void) const
{
	return this->_allocator.max_size();
}

/**
 *  Returns true if the %vector is empty.  (Thus begin() would
 *  equal end().)
 */
template <typename T>
bool
Vector<T>::empty(void) const
{
	return !(this->_size);
}

/**
 * Element access
 */

template <typename T>
T &
Vector<T>::operator[](size_t position) const
{
	return this->_list[position];
}

template <typename T>
T &
Vector<T>::at(size_t position) const
{
	if (this->size() <= position)
		throw out_of_range();
	return (*this)[position];
}

template <typename T>
T &
Vector<T>::front(void) const
{
	return this->_list[0];
}

template <typename T>
T &
Vector<T>::back(void) const
{
	return this->_list[this->_size - 1];
}

/**
 * Modifiers
 */

template <typename T>
void
Vector<T>::assign(size_t nElements, T value)
{
	message("Vector: assign");

	_allocator.deallocate(this->_list, this->_allocated);

	this->_size = nElements;
	this->_allocated = nElements;
	this->_maxSize = nElements;
	this->_list = _allocator.allocate(nElements);

	for (size_t i = 0; i < nElements; i++)
		this->_allocator.construct(&(this->_list[i]), value);
}

/**
 *  @brief  Add data to the end of the %vector.
 *  @param  object  Data to be added.
 *
 *  This is a typical stack operation.  The function creates an
 *  element at the end of the %vector and assigns the given data
 *  to it.  Due to the nature of a %vector this operation can be
 *  done in constant time if the %vector has preallocated space
 *  available.
 */
template <typename T>
void
Vector<T>::push_back(T const &object)
{
	T	  *newList;
	size_t newAllocation;

	message("Vector: push back");
	if (this->_allocated == this->_size)
	{
		newAllocation = this->_allocated * 2;
		newList = this->_allocator.allocate(newAllocation);
		for (size_t i = 0; i < this->_allocated; ++i)
		{
			this->_allocator.construct(&(newList[i]), (*this)[i]);
			this->_allocator.destroy(&(*this)[i]);
		}
		this->_allocator.construct(&(newList[this->_allocated]), object);
		this->_allocator.deallocate(this->_list, this->_allocated);
		this->_list = newList;
		this->_allocated = newAllocation;
		++this->_size;
	}
	else
	{
		this->_allocator.construct(&((*this)[this->_size]), object);
		++this->_size;
	}
}

/**
 *  @brief  Removes last element.
 *
 *  This is a typical stack operation. It shrinks the %vector by one.
 *
 *  Note that no data is returned, and if the last element's
 *  data is needed, it should be retrieved before pop_back() is
 *  called.
 */
template <typename T>
void
Vector<T>::pop_back(void)
{
	message("Vector: pop_back");

	if (this->empty())
		return;

	this->_allocator.destroy(&(*this)[this->_size - 1]);
	--this->_size;
}

template <typename T>
void
Vector<T>::swap(Vector &other)
{
	T	  *tmpList;
	size_t tmpAllocated;
	size_t tmpSize;

	tmpList = this->_list;
	tmpAllocated = this->_allocated;
	tmpSize = this->_size;

	this->_list = other._list;
	this->_allocated = other._allocated;
	this->_size = other._size;

	other._list = tmpList;
	other._allocated = tmpAllocated;
	other._size = tmpSize;
}

template <typename T>
void
Vector<T>::clear(void)
{
	message("Vector: clear");

	if (this->empty())
		return;

	for (size_t i = 0; i < this->_size; ++i)
		this->_allocator.destroy(&(*this)[i]);
	this->_allocator.deallocate(this->_list, this->_allocated);
	this->_allocated = 0;
	this->_size = 0;
	this->_list = 0;
}

/**
 * Extra...
 */

template <typename T>
std::ostream &
operator<<(std::ostream &output, Vector<T> const &vec)
{
	output << "(vector) = size=" << vec.size() << " {" << std::endl;
	for (size_t i = 0; i < vec.size(); i++)
		output << "  [" << i << "] = " << vec[i] << std::endl;
	output << "}" << std::endl;
	return output;
}
