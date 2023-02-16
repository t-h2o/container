/**
 * Node
 */

template <typename value_type> Node<value_type>::Node(Node *newparent) : parent(newparent)
{
	child[0] = 0;
	child[1] = 0;
	this->set_red();
}

template <typename value_type>
void
Node<value_type>::set_red(void)
{
	color.set_red();
}

template <typename value_type>
void
Node<value_type>::set_black(void)
{
	color.set_black();
}

template <typename value_type>
void
Node<value_type>::flip_color(void)
{
	if (color.is_red())
		this->set_black();
	else
		this->set_red();
}

template <typename value_type>
void
Node<value_type>::color_children_red(void)
{
	if (left())
		left()->set_red();
	if (right())
		right()->set_red();
}

template <typename value_type>
void
Node<value_type>::color_children_black(void)
{
	if (left())
		left()->set_black();
	if (right())
		right()->set_black();
}

template <typename value_type>
void
Node<value_type>::reset_parent(void)
{
	if (left())
		left()->parent = this;
	if (right())
		right()->parent = this;
}

template <typename value_type>
bool
Node<value_type>::is_leaf(void) const
{
	return !(left() || right());
}

template <typename value_type>
bool
Node<value_type>::is_black(void) const
{
	return (color.is_black());
}

template <typename value_type>
bool
Node<value_type>::is_red(void) const
{
	return (color.is_red());
}

template <typename value_type>
bool
Node<value_type>::has_red_child(void) const
{
	return ((left() && left()->is_red()) || (right() && right()->is_red()));
}

template <typename value_type>
bool
Node<value_type>::has_black_children() const
{
	return ((!(this->left()) || this->left()->is_black()) && (!(this->right()) || this->right()->is_black()));
}

template <typename value_type>
unsigned char
Node<value_type>::number_child() const
{
	return (!!(this->left()) + !!(this->right()));
}

template <typename value_type>
typename Node<value_type>::Node *&
Node<value_type>::right(void)
{
	return child[RIGHT];
}

template <typename value_type>
typename Node<value_type>::Node *
Node<value_type>::right(void) const
{
	return child[RIGHT];
}

template <typename value_type>
typename Node<value_type>::Node *&
Node<value_type>::left(void)
{
	return child[LEFT];
}

template <typename value_type>
typename Node<value_type>::Node *
Node<value_type>::left(void) const
{
	return child[LEFT];
}

template <typename value_type>
typename Node<value_type>::Node *
Node<value_type>::get_child() const
{
	if (this->left())
		return this->left();
	return this->right();
}

template <typename value_type>
typename Node<value_type>::Node *
Node<value_type>::get_grandparent() const
{
	if (this->parent)
		return this->parent->parent;
	return 0;
}

template <typename value_type>
typename Node<value_type>::Node *
Node<value_type>::get_uncle() const
{
	Node *grandParent(this->get_grandparent());

	if (grandParent == 0)
		return 0;
	if (grandParent->left() == this->parent)
		return grandParent->right();
	return grandParent->left();
}

template <typename value_type>
typename Node<value_type>::Node *
Node<value_type>::get_sibling() const
{
	enum e_side side(this->get_side());
	if (side == LEFT)
		side = RIGHT;
	else
		side = LEFT;

	return this->parent->child[side];
}

template <typename value_type>
typename Node<value_type>::Node *
Node<value_type>::get_predecessor() const
{
	Node *predecessor(this->left());

	while (predecessor->right())
		predecessor = predecessor->right();

	return predecessor;
}

template <typename value_type>
e_side
Node<value_type>::get_side() const
{
	if (this->parent == 0)
		throw(std::logic_error("get_side: this hasn't parent"));
	if (this->parent->right() == this)
	{
		if (RBT_LOG)
			std::cout << "get_side: " << this->key() << " is right of " << this->parent->key() << std::endl;
		return RIGHT;
	}
	else if (this->parent->left() == this)
	{
		if (RBT_LOG)
			std::cout << "get_side: " << this->key() << " is left of " << this->parent->key() << std::endl;
		return LEFT;
	}
	else
		throw(std::logic_error("get_side: \"this\" hasn't the good parent"));
}

template <typename value_type>
typename Node<value_type>::TYPE &
Node<value_type>::key(void)
{
	return dual;
}

template <typename value_type>
typename Node<value_type>::TYPE
Node<value_type>::key(void) const
{
	return dual;
}

/**
 * Side
 */

e_side
_flip_side(enum e_side side)
{
	if (side == LEFT)
		return RIGHT;
	else
		return LEFT;
}
