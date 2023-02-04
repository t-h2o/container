template <typename Key, typename T2> pair<Key, T2>::pair(void) {}

template <typename Key, typename T2>
pair<Key, T2>::pair(const pair &other) : first(other.first), second(other.second)
{
}

template <typename Key, typename T2> pair<Key, T2>::pair(Key const &f, T2 const &s) : first(f), second(s) {}

template <typename Key, typename T2>
pair<Key, T2> &
pair<Key, T2>::operator=(pair const &other)
{
	if (this == &other)
		return *this;

	this->first = other.first;
	this->second = other.second;

	return *this;
}

template <typename Key, typename T2>
pair<Key, T2> &
pair<Key, T2>::operator=(T2 const &value)
{
	this->second = value;

	return *this;
}

template <typename Key, typename T2>
std::ostream &
operator<<(std::ostream &output, pair<Key, T2> const &pair)
{
	output << "[" << pair.first << "] = " << pair.second;

	return output;
}
