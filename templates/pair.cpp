template <typename Key, typename Type> pair<Key, Type>::pair(void) {}

template <typename Key, typename Type>
pair<Key, Type>::pair(const pair &other) : first(other.first), second(other.second)
{
}

template <typename Key, typename Type>
pair<Key, Type>::pair(Key const &f, Type const &s) : first(f), second(s)
{
}

template <typename Key, typename Type>
pair<Key, Type> &
pair<Key, Type>::operator=(pair const &other)
{
	if (this == &other)
		return *this;

	this->first = other.first;
	this->second = other.second;

	return *this;
}

template <typename Key, typename Type>
pair<Key, Type> &
pair<Key, Type>::operator=(Type const &value)
{
	this->second = value;

	return *this;
}

template <class Key, class Type>
bool
pair<Key, Type>::operator==(const pair<Key, Type> &other)
{
	return this->first == other.first;
}

template <class Key, class Type>
bool
pair<Key, Type>::operator!=(const pair<Key, Type> &other)
{
	return this->first != other.first;
}

template <class Key, class Type>
bool
pair<Key, Type>::operator<(const pair<Key, Type> &other)
{
	return this->first < other.first;
}

template <class Key, class Type>
bool
pair<Key, Type>::operator<=(const pair<Key, Type> &other)
{
	return this->first <= other.first;
}

template <class Key, class Type>
bool
pair<Key, Type>::operator>(const pair<Key, Type> &other)
{
	return this->first > other.first;
}

template <class Key, class Type>
bool
pair<Key, Type>::operator>=(const pair<Key, Type> &other)
{
	return this->first >= other.first;
}

template <typename Key, typename Type>
void
pair<Key, Type>::swap(pair &other)
{
	Key	 tmp1;
	Type tmp2;

	tmp1 = this->first;
	tmp2 = this->second;

	this->first = other.first;
	this->second = other.second;

	other.first = tmp1;
	other.second = tmp2;
}

template <typename Key, typename Type>
std::ostream &
operator<<(std::ostream &output, pair<Key, Type> const &pair)
{
	output << "[" << pair.first << "] = " << pair.second;

	return output;
}
