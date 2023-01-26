// This file is included into headers/Vector.hpp

template <typename T> vector<T>::iterator::iterator(void) : _pointer(0), _position(0) {}

template <typename T>
vector<T>::iterator::iterator(T *pointer, size_t position) : _pointer(pointer), _position(position)
{
}

template <typename T>
T &
vector<T>::iterator::operator*(void)
{
	return this->_pointer[_position];
}

template <typename T>
T &
vector<T>::iterator::operator[](size_t position)
{
	return this->_pointer[_position + position];
}

template <typename T>
typename vector<T>::iterator &
vector<T>::iterator::operator++(void)
{
	this->_position++;
	return *this;
}

template <typename T>
typename vector<T>::iterator
vector<T>::iterator::operator++(int)
{
	vector<T>::iterator prev;

	prev = *this;
	this->_position++;
	return prev;
}

template <typename T>
typename vector<T>::iterator &
vector<T>::iterator::operator--(void)
{
	this->_position--;
	return *this;
}

template <typename T>
typename vector<T>::iterator
vector<T>::iterator::operator--(int)
{
	vector<T>::iterator prev;

	prev = *this;
	this->_position--;
	return prev;
}

template <typename T>
bool
vector<T>::iterator::operator==(vector<T>::iterator const &other)
{
	return (&(this->_pointer[this->_position]) == &(other._pointer[other._position]));
}

template <typename T>
bool
vector<T>::iterator::operator!=(vector<T>::iterator const &other)
{
	return !(*this == other);
}

template <typename T>
bool
vector<T>::iterator::operator>(vector<T>::iterator const &other)
{
	return (&(this->_pointer[this->_position]) > &(other._pointer[other._position]));
}

template <typename T>
bool
vector<T>::iterator::operator<(vector<T>::iterator const &other)
{
	return (&(this->_pointer[this->_position]) < &(other._pointer[other._position]));
}

template <typename T>
bool
vector<T>::iterator::operator>=(vector<T>::iterator const &other)
{
	return (!(*this < other));
}

template <typename T>
bool
vector<T>::iterator::operator<=(vector<T>::iterator const &other)
{
	return (!(*this > other));
}

template <typename T>
typename vector<T>::iterator
vector<T>::iterator::operator+(const long add)
{
	vector<T>::iterator diff(this->_pointer, this->_position + add);
	return diff;
}

template <typename T>
typename vector<T>::iterator
vector<T>::iterator::operator-(const long remove)
{
	vector<T>::iterator diff(this->_pointer, this->_position - remove);
	return diff;
}

template <typename T>
std::ptrdiff_t
vector<T>::iterator::operator-(iterator const &other)
{
	return this->_position - other._position;
}

template <typename T>
typename vector<T>::iterator &
vector<T>::iterator::operator+=(const long add)
{
	this->_position += add;
	return *this;
}

template <typename T>
typename vector<T>::iterator &
vector<T>::iterator::operator-=(const long remove)
{
	this->_position -= remove;
	return *this;
}
