/**
 * Color
 */

template <typename Key, typename T2, typename Alloc>
void
map<Key, T2, Alloc>::Color::flip(void)
{
	if (this->is_red())
		this->set_black();
	else
		this->set_red();
}

template <typename Key, typename T2, typename Alloc>
bool
map<Key, T2, Alloc>::Color::is_red(void) const
{
	return (this->_color == RED);
}

template <typename Key, typename T2, typename Alloc>
bool
map<Key, T2, Alloc>::Color::is_black(void) const
{
	return (this->_color == BLACK);
}

template <typename Key, typename T2, typename Alloc>
void
map<Key, T2, Alloc>::Color::set_red(void)
{
	this->_color = RED;
}

template <typename Key, typename T2, typename Alloc>
void
map<Key, T2, Alloc>::Color::set_black(void)
{
	this->_color = BLACK;
}
