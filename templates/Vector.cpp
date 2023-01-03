// This file is included into headers/Iterator.hpp

/**
 * Member Funcion
 */

template <typename T>
vector<T>::vector(void) : _list(0), _maxSize(0), _size(0), _allocated(0)
{
}

template <typename T>
vector<T>::vector(vector const &other)
	: _list(0), _maxSize(0), _size(0), _allocated(0)
{
	*this = other;
}

template <typename T> vector<T>::~vector(void)
{
	this->clear();
	this->_allocator.deallocate(this->_list, this->_allocated);
}

template <typename T>
vector<T> &
vector<T>::operator=(vector const &other)
{
	if (this == &other)
		return *this;

	this->clear();
	if (this->_allocated < other._allocated)
	{
		this->_allocator.deallocate(this->_list, this->_allocated);
		this->_list = this->_allocator.allocate(other._size);
	}
	this->_size = other._size;
	this->_allocated = other._size;

	for (size_t i = 0; i < other._size; ++i)
	{
		this->_allocator.construct(&(*this)[i], other[i]);
	}

	return *this;
}

template <typename T>
typename vector<T>::iterator
vector<T>::begin(void)
{
	return iterator(this->_list, 0);
}

template <typename T>
typename vector<T>::iterator
vector<T>::end(void)
{
	return iterator(this->_list, this->_size);
}

/**
 * Capacity
 */

template <typename T>
size_t
vector<T>::size(void) const
{
	return this->_size;
}

template <typename T>
size_t
vector<T>::max_size(void) const
{
	return this->_allocator.max_size();
}

template <typename T>
void
vector<T>::resize(size_t newSize)
{
	T *newList;

	size_t newAllocation = this->_allocated;
	while (newSize > newAllocation)
		newAllocation *= 2;

	newList = this->_allocator.allocate(newAllocation);

	for (size_t i = 0; i < newSize; i++)
	{
		if (i < this->_size)
			this->_allocator.construct(&(newList[i]), (*this)[i]);
		else
			this->_allocator.construct(&(newList[i]));
	}

	this->_destroy_all();

	this->_allocator.deallocate(this->_list, this->_allocated);
	this->_size = newSize;
	this->_allocated = newAllocation;
	this->_list = newList;
}

template <typename T>
size_t
vector<T>::capacity(void) const
{
	return this->_allocated;
}

/**
 *  Returns true if the %vector is empty.  (Thus begin() would
 *  equal end().)
 */
template <typename T>
bool
vector<T>::empty(void) const
{
	return !(this->_size);
}

template <typename T>
void
vector<T>::reserve(size_t newAllocation)
{
	T *newList;

	if (newAllocation <= this->_allocated)
		return;

	newList = this->_gen_new_list(newAllocation);

	this->_destroy_all();

	this->_allocator.deallocate(this->_list, this->_allocated);
	this->_allocated = newAllocation;
	this->_list = newList;
}

template <typename T>
void
vector<T>::shrink_to_fit(void)
{
	size_t newAllocation;
	T	  *newList;

	if (this->_allocated == this->_size)
		return;

	newAllocation = this->_size;
	newList = this->_gen_new_list(newAllocation);
	this->_destroy_all();
	this->_allocator.deallocate(this->_list, this->_allocated);
	this->_allocated = this->_size;
	this->_list = newList;
}

/**
 * Element access
 */

template <typename T>
T &
vector<T>::operator[](size_t position) const
{
	return this->_list[position];
}

template <typename T>
T &
vector<T>::at(size_t position) const
{
	if (this->size() <= position)
		throw out_of_range();
	return (*this)[position];
}

template <typename T>
T &
vector<T>::front(void) const
{
	return this->_list[0];
}

template <typename T>
T &
vector<T>::back(void) const
{
	return this->_list[this->_size - 1];
}

template <typename T>
T *
vector<T>::data(void) const
{
	return this->_list;
}

/**
 * Modifiers
 */

template <typename T>
void
vector<T>::assign(size_t nElements, T value)
{

	if (this->_list == 0)
	{
		// first allocation
		this->_size = nElements;
		this->_allocated = nElements;
		this->_maxSize = nElements;
		this->_list = _allocator.allocate(nElements);

		_construct_val(value);
	}
	else if (nElements >= this->_size)
	{
		// reallocation
		this->_destroy_all();
		this->_allocator.deallocate(this->_list, this->_allocated);
		this->_size = nElements;
		this->_allocated = nElements;
		this->_maxSize = nElements;
		this->_list = _allocator.allocate(nElements);

		_construct_val(value);
	}
	else if (nElements < this->_size)
	{
		// destroy and construct

		_destroy_all();
		this->_size = nElements;

		_construct_val(value);
	}
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
vector<T>::push_back(T const &object)
{
	T	  *newList;
	size_t newAllocation;

	if (this->_list == 0)
	{
		this->_list = this->_allocator.allocate(1);
		this->_allocator.construct(this->_list, object);
		this->_allocated = 1;
		this->_size = 1;
	}
	else if (this->_allocated == this->_size)
	{
		newAllocation = this->_allocated * 2;
		newList = this->_gen_new_list(newAllocation);
		this->_destroy_all();
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
vector<T>::pop_back(void)
{
	if (this->empty())
		return;

	this->_allocator.destroy(&(*this)[this->_size - 1]);
	--this->_size;
}

template <typename T>
void
vector<T>::erase(iterator position)
{
	T *newList;

	if (position == this->end() - 1)
	{
		this->_allocator.destroy(&(position[0]));
		--this->_size;
		return;
	}

	newList = this->_allocator.allocate(this->_allocated);
	for (size_t i = 0, j = 0; i < this->_size; ++i)
	{
		if (&((*this)[i]) != &(position[0]))
		{
			this->_allocator.construct(&(newList[j]), ((*this)[i]));
			++j;
		}
		this->_allocator.destroy(&(*this)[i]);
	}
	this->_allocator.deallocate(this->_list, this->_allocated);
	--this->_size;
	this->_list = newList;
}

template <typename T>
void
vector<T>::erase(iterator first, iterator last)
{
	T *newList;

	if (last == this->end())
	{
		for (iterator it = first; it != last; it++)
			this->_allocator.destroy(&(it[0]));

		this->_size -= last - first;
		return;
	}

	newList = this->_allocator.allocate(this->_allocated);
	for (size_t i = 0, j = 0; i < this->_size; ++i)
	{
		if (&((*this)[i]) < &(first[0]) || &(last[0]) <= &((*this)[i]))
		{
			this->_allocator.construct(&(newList[j]), ((*this)[i]));
			++j;
		}
		this->_allocator.destroy(&(*this)[i]);
	}
	this->_allocator.deallocate(this->_list, this->_allocated);
	this->_size -= last - first;
	this->_list = newList;
}

template <typename T>
void
vector<T>::swap(vector &other)
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
vector<T>::clear(void)
{
	if (this->empty())
		return;

	this->_destroy_all();

	this->_size = 0;
}

/**
 * Extra...
 */

template <typename T>
void
vector<T>::_destroy_all(void)
{
	for (size_t i = 0; i < this->_size; ++i)
		this->_allocator.destroy(&((*this)[i]));
}

template <typename T>
void
vector<T>::_construct_val(T &value)
{
	for (size_t i = 0; i < this->_size; i++)
		this->_allocator.construct(&(this->_list[i]), value);
}

template <typename T>
T *
vector<T>::_gen_new_list(size_t newAllocation)
{
	T *newList;

	newList = this->_allocator.allocate(newAllocation);
	for (size_t i = 0; i < this->_size; ++i)
	{
		this->_allocator.construct(&(newList[i]), (*this)[i]);
	}

	return newList;
}

template <typename T>
std::ostream &
operator<<(std::ostream &output, vector<T> const &vec)
{
	output << "(vector) = size=" << vec.size()
		   << ", capacity=" << vec.capacity() << " {" << std::endl;
	for (size_t i = 0; i < vec.size(); i++)
		output << "  [" << i << "] = " << vec[i] << std::endl;
	output << "}" << std::endl;
	return output;
}
