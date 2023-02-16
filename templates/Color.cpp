/**
 * Color
 */

void
Color::flip(void)
{
	if (this->is_red())
		this->set_black();
	else
		this->set_red();
}

bool
Color::is_red(void) const
{
	return (this->_color == RED);
}

bool
Color::is_black(void) const
{
	return (this->_color == BLACK);
}

void
Color::set_red(void)
{
	this->_color = RED;
}

void
Color::set_black(void)
{
	this->_color = BLACK;
}
