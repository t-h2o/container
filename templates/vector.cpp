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
	_allocator.deallocate(_list, _allocated);
}

template <typename T, typename Alloc>
vector<T, Alloc> &
vector<T, Alloc>::operator=(vector const &other)
{
	if (this == &other)
		return *this;

	this->clear();
	if (_allocated < other._allocated)
	{
		_allocator.deallocate(_list, _allocated);
		_list = _allocator.allocate(other._size);
	}
	_size = other._size;
	_allocated = other._size;

	for (size_type i = 0; i < other._size; ++i)
	{
		_allocator.construct(&(*this)[i], other[i]);
	}

	return *this;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::begin(void)
{
	return iterator(_list);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::iterator
vector<T, Alloc>::end(void)
{
	return iterator(&(_list[_size]));
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator
vector<T, Alloc>::begin(void) const
{
	return const_iterator(_list);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_iterator
vector<T, Alloc>::end(void) const
{
	return const_iterator(&(_list[_size]));
}

/* reverse iterator */

template <typename T, typename Alloc>
typename vector<T, Alloc>::reverse_iterator
vector<T, Alloc>::rbegin(void)
{
	return reverse_iterator(this->end());
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reverse_iterator
vector<T, Alloc>::rend(void)
{
	return reverse_iterator(this->begin());
}

/* const reverse iterator */

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reverse_iterator
vector<T, Alloc>::rbegin(void) const
{
	return const_reverse_iterator(this->end());
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::const_reverse_iterator
vector<T, Alloc>::rend(void) const
{
	return const_reverse_iterator(this->begin());
}

/**
 * Capacity
 */

template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type
vector<T, Alloc>::size(void) const
{
	return _size;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type
vector<T, Alloc>::max_size(void) const
{
	return _allocator.max_size();
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::resize(size_type newSize)
{
	pointer newList;

	size_type newAllocation;

	if (newSize < _allocated)
	{
		size_type i = _size;
		while (i >= newSize)
		{
			_allocator.destroy(&(_list[i--]));
		}
		_size = newSize;
		return;
	}
	newAllocation = this->_new_size(newSize);

	newList = _allocator.allocate(newAllocation);

	for (size_type i = 0; i < newSize; i++)
	{
		if (i < _size)
			_allocator.construct(&(newList[i]), (*this)[i]);
		else
			_allocator.construct(&(newList[i]), T());
	}

	this->_destroy_all();

	_allocator.deallocate(_list, _allocated);
	_size = newSize;
	_allocated = newAllocation;
	_list = newList;
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type
vector<T, Alloc>::capacity(void) const
{
	return _allocated;
}

/**
 *  Returns true if the %vector is empty.  (Thus begin() would
 *  equal end().)
 */
template <typename T, typename Alloc>
bool
vector<T, Alloc>::empty(void) const
{
	return !(_size);
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::reserve(size_type newAllocation)
{
	pointer newList;

	if (newAllocation <= _allocated)
		return;

	newList = this->_gen_new_list(newAllocation);

	this->_destroy_all();

	_allocator.deallocate(_list, _allocated);
	_allocated = newAllocation;
	_list = newList;
}

/**
 * Element access
 */

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference
vector<T, Alloc>::operator[](size_type position) const
{
	return _list[position];
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
	return _list[0];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::reference
vector<T, Alloc>::back(void) const
{
	return _list[_size - 1];
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::pointer
vector<T, Alloc>::data(void) const
{
	return _list;
}

/**
 * Modifiers
 */

template <typename T, typename Alloc>
void
vector<T, Alloc>::assign(size_type nElements, T value)
{

	if (_list == 0)
	{
		// first allocation
		_first_allocation(nElements);

		_construct_value(value);
	}
	else if (nElements >= _size)
	{
		// reallocation
		this->_destroy_all();
		_allocator.deallocate(_list, _allocated);
		_size = nElements;
		_allocated = nElements;
		_list = _allocator.allocate(nElements);

		_construct_value(value);
	}
	else if (nElements < _size)
	{
		// destroy and construct

		_destroy_all();
		_size = nElements;

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

	if (_list == 0)
	{
		_first_allocation(length);

		_construct_range(_list, first, last);
	}
	else if (static_cast<size_type>(length) >= _size)
	{
		// reallocation
		this->_destroy_all();
		_allocator.deallocate(_list, _allocated);

		_first_allocation(length);

		_construct_range(_list, first, last);
	}
	else if (static_cast<size_type>(length) < _size)
	{
		// destroy and construct

		_destroy_all();
		_size = length;

		_construct_range(_list, first, last);
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

	if (_list == 0)
	{
		_list = _allocator.allocate(1);
		_allocator.construct(_list, object);
		_allocated = 1;
		_size = 1;
	}
	else if (_allocated == _size)
	{
		newAllocation = this->_new_size(_size + 1);
		newList = this->_gen_new_list(newAllocation);
		this->_destroy_all();
		_allocator.construct(&(newList[_allocated]), object);
		_allocator.deallocate(_list, _allocated);
		_list = newList;
		_allocated = newAllocation;
		++_size;
	}
	else
	{
		_allocator.construct(&((*this)[_size]), object);
		++_size;
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

	_allocator.destroy(&(*this)[_size - 1]);
	--_size;
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::insert(iterator position, const_reference value)
{
	pointer	  newList;
	size_type i;
	size_type newAllocation;

	if (_size + 1 <= _allocated)
	{
		iterator it = this->end();

		_allocator.construct(&(it[0]), value);
		for (; it != position; --it)
			*it = *(it - 1);
		*position = value;
	}
	else
	{
		i = 0;
		newAllocation = this->_new_size(_size + 1);
		newList = _allocator.allocate(newAllocation);
		for (iterator it = this->begin(); it != position; it++)
		{
			_allocator.construct(&(newList[i++]), *it);
			_allocator.destroy(&(it[0]));
		}
		_allocator.construct(&(newList[i++]), value);
		for (iterator it = position; it != this->end(); it++)
		{
			_allocator.construct(&(newList[i++]), *it);
			_allocator.destroy(&(it[0]));
		}
		_allocator.deallocate(_list, _allocated);
		_allocated = newAllocation;
		_list = newList;
	}
	_size++;
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::insert(iterator position, size_type number, const_reference value)
{
	size_type i;
	pointer	  newList;
	size_type newAllocation;

	if (_size + number < _allocated)
	{
		iterator it(this->end());

		for (; it != this->end() + number; ++it)
			_allocator.construct(&(*it), *(it - number));

		it = this->end() - 1;
		_size += number;

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

		newAllocation = this->_new_size(_size + number);

		newList = _allocator.allocate(newAllocation);

		for (; it != position; it++)
		{
			_allocator.construct(&(newList[i++]), *it);
			_allocator.destroy(&(it[0]));
		}

		for (size_type j = number; j; --j)
			_allocator.construct(&(newList[i++]), value);

		for (iterator it = position; it != this->end(); it++)
		{
			_allocator.construct(&(newList[i++]), *it);
			_allocator.destroy(&(it[0]));
		}

		_allocator.deallocate(_list, _allocated);
		_allocated = newAllocation;
		_list = newList;
		_size += number;
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

	if (_size + length < _allocated)
	{
		iterator it(this->end());

		for (; it != this->end() + length; ++it)
			_allocator.construct(&(*it), *(it - length));

		it = this->end() - 1;
		_size += length;

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

		newAllocation = this->_new_size(_size + length);

		newList = _allocator.allocate(newAllocation);

		for (; it != position; it++)
		{
			_allocator.construct(&(newList[i++]), *it);
			_allocator.destroy(&(it[0]));
		}

		_construct_range(&(newList[i]), first, last);
		i += length;

		for (iterator it = position; it != this->end(); it++)
		{
			_allocator.construct(&(newList[i++]), *it);
			_allocator.destroy(&(it[0]));
		}

		_allocator.deallocate(_list, _allocated);
		_allocated = newAllocation;
		_list = newList;
		_size += length;
	}
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::erase(iterator position)
{
	pointer newList;

	if (position == this->end() - 1)
	{
		_allocator.destroy(&(position[0]));
		--_size;
		return;
	}

	newList = _allocator.allocate(_allocated);
	for (size_type i = 0, j = 0; i < _size; ++i)
	{
		if (&((*this)[i]) != &(position[0]))
		{
			_allocator.construct(&(newList[j]), ((*this)[i]));
			++j;
		}
		_allocator.destroy(&(*this)[i]);
	}
	_allocator.deallocate(_list, _allocated);
	--_size;
	_list = newList;
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::erase(iterator first, iterator last)
{
	pointer newList;

	if (last == this->end())
	{
		for (iterator it = first; it != last; it++)
			_allocator.destroy(&(it[0]));

		_size -= last - first;
		return;
	}

	newList = _allocator.allocate(_allocated);
	for (size_type i = 0, j = 0; i < _size; ++i)
	{
		if (&((*this)[i]) < &(first[0]) || &(last[0]) <= &((*this)[i]))
		{
			_allocator.construct(&(newList[j]), ((*this)[i]));
			++j;
		}
		_allocator.destroy(&(*this)[i]);
	}
	_allocator.deallocate(_list, _allocated);
	_size -= last - first;
	_list = newList;
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::swap(vector &other)
{
	pointer	  tmpList;
	size_type tmpAllocated;
	size_type tmpSize;

	tmpList = _list;
	tmpAllocated = _allocated;
	tmpSize = _size;

	_list = other._list;
	_allocated = other._allocated;
	_size = other._size;

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

	_size = 0;
}

/**
 * Extra...
 */

template <typename T, typename Alloc>
void
vector<T, Alloc>::_destroy_all(void)
{
	for (size_type i = 0; i < _size; ++i)
		_allocator.destroy(&((*this)[i]));
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::_construct_value(const_reference value)
{
	for (size_type i = 0; i < _size; i++)
		_allocator.construct(&(_list[i]), value);
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::_construct_range(pointer list, iterator first, iterator last)
{
	size_type index;

	index = 0;
	for (; first != last; ++first)
		_allocator.construct(&(list[index++]), *first);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::pointer
vector<T, Alloc>::_gen_new_list(size_type newAllocation)
{
	pointer newList;

	newList = _allocator.allocate(newAllocation);
	for (size_type i = 0; i < _size; ++i)
	{
		_allocator.construct(&(newList[i]), (*this)[i]);
	}

	return newList;
}

template <typename T, typename Alloc>
void
vector<T, Alloc>::_first_allocation(size_type newAllocation)
{
	_allocated = newAllocation;
	_size = newAllocation;
	_list = _allocator.allocate(_allocated);
}

template <typename T, typename Alloc>
typename vector<T, Alloc>::size_type
vector<T, Alloc>::_new_size(size_type minimum) const
{
	if (_allocated * 2 > minimum)
#ifdef __APPLE__
		return _allocated * 2;
#else
		return this->_size * 2;
#endif /* __APPLE__ */
	else
		return minimum;
}

#ifndef __APPLE__
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
#endif
