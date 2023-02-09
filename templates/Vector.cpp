// This file is included into headers/Iterator.hpp

/**
 * Member Funcion
 */

template <typename T, typename Alloc>
vector<T, Alloc>::vector(const allocator_type &alloc) : _list(0), _size(0), _allocated(0), _allocator(alloc)
{
}

template <typename T, typename Alloc>
vector<T, Alloc>::vector(size_type nElements, const_reference value, const allocator_type &alloc)
	: _list(0), _size(0), _allocated(0), _allocator(alloc)
{
	if (nElements == 0)
		return;

	_first_allocation(nElements);

	_construct_value(value);
}

template <typename T, typename Alloc>
vector<T, Alloc>::vector(iterator first, iterator last, const allocator_type &alloc)
	: _list(0), _size(0), _allocated(0), _allocator(alloc)
{
	difference_type length;

	length = last - first;
	if (length == 0)
		return;

	_first_allocation(length);

	_construct_range(this->data(), first, last);
}

template <typename T, typename Alloc>
vector<T, Alloc>::vector(vector const &other) : _list(0), _size(0), _allocated(0)
{
	*this = other;
}

template <typename T, typename Alloc> vector<T, Alloc>::~vector(void)
{
	this->clear();
	this->_allocator.deallocate(this->_list, this->_allocated);
}

template <typename T, typename Alloc>
vector<T, Alloc> &
vector<T, Alloc>::operator=(vector const &other)
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

	for (size_type i = 0; i < other._size; ++i)
	{
		this->_allocator.construct(&(*this)[i], other[i]);
	}

	return *this;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::begin(void)
{
	return iterator(this->_list);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::end(void)
{
	return iterator(&(this->_list[_size]));
}

/**
 * Capacity
 */

template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type
vector<T, Alloc>::size(void) const
{
	return this->_size;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type
vector<T, Alloc>::max_size(void) const
{
	return this->_allocator.max_size();
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::resize(size_type newSize)
{
	pointer newList;

	size_type newAllocation;

	if (newSize < this->_allocated)
	{
		size_type i = this->_size;
		while (i >= newSize)
		{
			this->_allocator.destroy(&(this->_list[i--]));
		}
		this->_size = newSize;
		return;
	}
	newAllocation = this->_new_size(newSize);

	newList = this->_allocator.allocate(newAllocation);

	for (size_type i = 0; i < newSize; i++)
	{
		if (i < this->_size)
			this->_allocator.construct(&(newList[i]), (*this)[i]);
		else
			this->_allocator.construct(&(newList[i]), T());
	}

	this->_destroy_all();

	this->_allocator.deallocate(this->_list, this->_allocated);
	this->_size = newSize;
	this->_allocated = newAllocation;
	this->_list = newList;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type
vector<T, Alloc>::capacity(void) const
{
	return this->_allocated;
}

/**
 *  Returns true if the %vector is empty.  (Thus begin() would
 *  equal end().)
 */
template <typename T, typename Alloc>
bool
vector<T, Alloc>::empty(void) const
{
	return !(this->_size);
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::reserve(size_type newAllocation)
{
	pointer newList;

	if (newAllocation <= this->_allocated)
		return;

	newList = this->_gen_new_list(newAllocation);

	this->_destroy_all();

	this->_allocator.deallocate(this->_list, this->_allocated);
	this->_allocated = newAllocation;
	this->_list = newList;
}

/**
 * Element access
 */

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference
vector<T, Alloc>::operator[](size_type position) const
{
	return this->_list[position];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference
vector<T, Alloc>::at(size_type position) const
{
	if (this->size() <= position)
		throw out_of_range();
	return (*this)[position];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference
vector<T, Alloc>::front(void) const
{
	return this->_list[0];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference
vector<T, Alloc>::back(void) const
{
	return this->_list[this->_size - 1];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::pointer
vector<T, Alloc>::data(void) const
{
	return this->_list;
}

/**
 * Modifiers
 */

template <typename T, typename Alloc>
void
vector<T, Alloc>::assign(size_type nElements, T value)
{

	if (this->_list == 0)
	{
		// first allocation
		_first_allocation(nElements);

		_construct_value(value);
	}
	else if (nElements >= this->_size)
	{
		// reallocation
		this->_destroy_all();
		this->_allocator.deallocate(this->_list, this->_allocated);
		this->_size = nElements;
		this->_allocated = nElements;
		this->_list = _allocator.allocate(nElements);

		_construct_value(value);
	}
	else if (nElements < this->_size)
	{
		// destroy and construct

		_destroy_all();
		this->_size = nElements;

		_construct_value(value);
	}
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::assign(iterator first, iterator last)
{
	difference_type length;

	length = last - first;
	if (length == 0)
		return;

	if (this->_list == 0)
	{
		_first_allocation(length);

		_construct_range(this->_list, first, last);
	}
	else if (static_cast<size_type>(length) >= this->_size)
	{
		// reallocation
		this->_destroy_all();
		this->_allocator.deallocate(this->_list, this->_allocated);

		_first_allocation(length);

		_construct_range(this->_list, first, last);
	}
	else if (static_cast<size_type>(length) < this->_size)
	{
		// destroy and construct

		_destroy_all();
		this->_size = length;

		_construct_range(this->_list, first, last);
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
template <typename T, typename Alloc>
void
vector<T, Alloc>::push_back(T const &object)
{
	pointer	  newList;
	size_type newAllocation;

	if (this->_list == 0)
	{
		this->_list = this->_allocator.allocate(1);
		this->_allocator.construct(this->_list, object);
		this->_allocated = 1;
		this->_size = 1;
	}
	else if (this->_allocated == this->_size)
	{
		newAllocation = this->_new_size(this->_size + 1);
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
template <typename T, typename Alloc>
void
vector<T, Alloc>::pop_back(void)
{
	if (this->empty())
		return;

	this->_allocator.destroy(&(*this)[this->_size - 1]);
	--this->_size;
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::insert(iterator position, const_reference value)
{
	pointer	  newList;
	size_type i;
	size_type newAllocation;

	if (this->_size + 1 <= this->_allocated)
	{
		iterator it = this->end();

		this->_allocator.construct(&(it[0]), value);
		for (; it != position; --it)
			*it = *(it - 1);
		*position = value;
	}
	else
	{
		i = 0;
		newAllocation = this->_new_size(this->_size + 1);
		newList = this->_allocator.allocate(newAllocation);
		for (iterator it = this->begin(); it != position; it++)
		{
			this->_allocator.construct(&(newList[i++]), *it);
			this->_allocator.destroy(&(it[0]));
		}
		this->_allocator.construct(&(newList[i++]), value);
		for (iterator it = position; it != this->end(); it++)
		{
			this->_allocator.construct(&(newList[i++]), *it);
			this->_allocator.destroy(&(it[0]));
		}
		this->_allocator.deallocate(this->_list, this->_allocated);
		this->_allocated = newAllocation;
		this->_list = newList;
	}
	this->_size++;
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::insert(iterator position, size_type number, const_reference value)
{
	size_type i;
	pointer	  newList;
	size_type newAllocation;

	if (this->_size + number < this->_allocated)
	{
		iterator it(this->end());

		for (; it != this->end() + number; ++it)
			this->_allocator.construct(&(*it), *(it - number));

		it = this->end() - 1;
		this->_size += number;

		for (; it != position; --it)
			*it = *(it - number);

		it = position;
		for (i = 0; i < number; i++)
			*(it + i) = value;
	}
	else
	{
		i = 0;
		iterator it(this->begin());

		newAllocation = this->_new_size(this->_size + number);

		newList = this->_allocator.allocate(newAllocation);

		for (; it != position; it++)
		{
			this->_allocator.construct(&(newList[i++]), *it);
			this->_allocator.destroy(&(it[0]));
		}

		for (size_type j = number; j; --j)
			this->_allocator.construct(&(newList[i++]), value);

		for (iterator it = position; it != this->end(); it++)
		{
			this->_allocator.construct(&(newList[i++]), *it);
			this->_allocator.destroy(&(it[0]));
		}

		this->_allocator.deallocate(this->_list, this->_allocated);
		this->_allocated = newAllocation;
		this->_list = newList;
		this->_size += number;
	}
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::insert(iterator position, iterator first, iterator last)
{
	difference_type length;
	size_type		i;
	pointer			newList;
	size_type		newAllocation;

	length = last - first;

	if (this->_size + length < this->_allocated)
	{
		iterator it(this->end());

		for (; it != this->end() + length; ++it)
			this->_allocator.construct(&(*it), *(it - length));

		it = this->end() - 1;
		this->_size += length;

		for (; it != position && this->begin() != (it - length); --it)
			*it = *(it - length);

		it = position;

		for (; first != last; ++first)
			(*(it++)) = *first;
	}
	else
	{
		i = 0;
		iterator it(this->begin());

		newAllocation = this->_new_size(this->_size + length);

		newList = this->_allocator.allocate(newAllocation);

		for (; it != position; it++)
		{
			this->_allocator.construct(&(newList[i++]), *it);
			this->_allocator.destroy(&(it[0]));
		}

		_construct_range(&(newList[i]), first, last);
		i += length;

		for (iterator it = position; it != this->end(); it++)
		{
			this->_allocator.construct(&(newList[i++]), *it);
			this->_allocator.destroy(&(it[0]));
		}

		this->_allocator.deallocate(this->_list, this->_allocated);
		this->_allocated = newAllocation;
		this->_list = newList;
		this->_size += length;
	}
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::erase(iterator position)
{
	pointer newList;

	if (position == this->end() - 1)
	{
		this->_allocator.destroy(&(position[0]));
		--this->_size;
		return;
	}

	newList = this->_allocator.allocate(this->_allocated);
	for (size_type i = 0, j = 0; i < this->_size; ++i)
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

template <typename T, typename Alloc>
void
vector<T, Alloc>::erase(iterator first, iterator last)
{
	pointer newList;

	if (last == this->end())
	{
		for (iterator it = first; it != last; it++)
			this->_allocator.destroy(&(it[0]));

		this->_size -= last - first;
		return;
	}

	newList = this->_allocator.allocate(this->_allocated);
	for (size_type i = 0, j = 0; i < this->_size; ++i)
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

template <typename T, typename Alloc>
void
vector<T, Alloc>::swap(vector &other)
{
	pointer	  tmpList;
	size_type tmpAllocated;
	size_type tmpSize;

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

template <typename T, typename Alloc>
void
vector<T, Alloc>::clear(void)
{
	if (this->empty())
		return;

	this->_destroy_all();

	this->_size = 0;
}

/**
 * Extra...
 */

template <typename T, typename Alloc>
void
vector<T, Alloc>::_destroy_all(void)
{
	for (size_type i = 0; i < this->_size; ++i)
		this->_allocator.destroy(&((*this)[i]));
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::_construct_value(const_reference value)
{
	for (size_type i = 0; i < this->_size; i++)
		this->_allocator.construct(&(this->_list[i]), value);
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::_construct_range(pointer list, iterator first, iterator last)
{
	size_type index;

	index = 0;
	for (; first != last; ++first)
		this->_allocator.construct(&(list[index++]), *first);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::pointer
vector<T, Alloc>::_gen_new_list(size_type newAllocation)
{
	pointer newList;

	newList = this->_allocator.allocate(newAllocation);
	for (size_type i = 0; i < this->_size; ++i)
	{
		this->_allocator.construct(&(newList[i]), (*this)[i]);
	}

	return newList;
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::_first_allocation(size_type newAllocation)
{
	this->_allocated = newAllocation;
	this->_size = newAllocation;
	this->_list = this->_allocator.allocate(this->_allocated);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type
vector<T, Alloc>::_new_size(size_type minimum) const
{
	if (this->_allocated * 2 > minimum)
		return this->_size * 2;
	else
		return minimum;
}

template <typename T>
std::ostream &
operator<<(std::ostream &output, vector<T> const &vec)
{
	output << "(vector) = size=" << vec.size() << ", capacity=" << vec.capacity() << " {" << std::endl;
	for (size_t i = 0; i < vec.size(); i++)
		output << "  [" << i << "] = " << vec[i] << std::endl;
	output << "}" << std::endl;
	return output;
}
