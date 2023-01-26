/**
 * Color
 */

template <typename T1, typename T2>
void
map<T1, T2>::Color::flip(void)
{
	if (this->is_red())
		this->set_black();
	else
		this->set_red();
}

template <typename T1, typename T2>
bool
map<T1, T2>::Color::is_red(void) const
{
	return (this->_color == RED);
}

template <typename T1, typename T2>
bool
map<T1, T2>::Color::is_black(void) const
{
	return (this->_color == BLACK);
}

template <typename T1, typename T2>
void
map<T1, T2>::Color::set_red(void)
{
	this->_color = RED;
}

template <typename T1, typename T2>
void
map<T1, T2>::Color::set_black(void)
{
	this->_color = BLACK;
}
