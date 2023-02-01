template <typename T1, typename T2> pair<T1, T2>::pair(void) {}

template <typename T1, typename T2>
pair<T1, T2>::pair(const pair &other) : first(other.first), second(other.second)
{
}

template <typename T1, typename T2> pair<T1, T2>::pair(T1 const &f, T2 const &s) : first(f), second(s) {}

template <typename T1, typename T2>
pair<T1, T2> &
pair<T1, T2>::operator=(pair const &other)
{
	if (this == &other)
		return *this;

	this->first = other.first;
	this->second = other.second;

	return *this;
}

template <typename T1, typename T2>
pair<T1, T2> &
pair<T1, T2>::operator=(T2 const &value)
{
	this->second = value;

	return *this;
}

template <typename T1, typename T2>
std::ostream &
operator<<(std::ostream &output, pair<T1, T2> const &pair)
{
	output << "[" << pair.first << "] = " << pair.second;

	return output;
}
