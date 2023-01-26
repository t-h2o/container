/**
 * Node
 */

template <typename T1, typename T2> map<T1, T2>::Node::Node(Node *newparent) : parent(newparent)
{
	child[0] = 0;
	child[1] = 0;
	this->set_red();
}

template <typename T1, typename T2>
void
map<T1, T2>::Node::set_red(void)
{
	color.set_red();
}

template <typename T1, typename T2>
void
map<T1, T2>::Node::set_black(void)
{
	color.set_black();
}

template <typename T1, typename T2>
void
map<T1, T2>::Node::flip_color(void)
{
	if (color.is_red())
		this->set_black();
	else
		this->set_red();
}

template <typename T1, typename T2>
void
map<T1, T2>::Node::color_children_red(void)
{
	if (left())
		left()->set_red();
	if (right())
		right()->set_red();
}

template <typename T1, typename T2>
void
map<T1, T2>::Node::color_children_black(void)
{
	if (left())
		left()->set_black();
	if (right())
		right()->set_black();
}

template <typename T1, typename T2>
void
map<T1, T2>::Node::reset_parent(void)
{
	if (left())
		left()->parent = this;
	if (right())
		right()->parent = this;
}

template <typename T1, typename T2>
bool
map<T1, T2>::Node::is_leaf(void) const
{
	return !(left() || right());
}

template <typename T1, typename T2>
bool
map<T1, T2>::Node::is_black(void) const
{
	return (color.is_black());
}

template <typename T1, typename T2>
bool
map<T1, T2>::Node::is_red(void) const
{
	return (color.is_red());
}

template <typename T1, typename T2>
bool
map<T1, T2>::Node::has_red_child(void) const
{
	return ((left() && left()->is_red()) || (right() && right()->is_red()));
}

template <typename T1, typename T2>
bool
map<T1, T2>::Node::has_black_children() const
{
	return ((!(this->left()) || this->left()->is_black()) && (!(this->right()) || this->right()->is_black()));
}

template <typename T1, typename T2>
unsigned char
map<T1, T2>::Node::number_child() const
{
	return (!!(this->left()) + !!(this->right()));
}

template <typename T1, typename T2>
typename map<T1, T2>::Node *&
map<T1, T2>::Node::right(void)
{
	return child[RIGHT];
}

template <typename T1, typename T2>
typename map<T1, T2>::Node *
map<T1, T2>::Node::right(void) const
{
	return child[RIGHT];
}

template <typename T1, typename T2>
typename map<T1, T2>::Node *&
map<T1, T2>::Node::left(void)
{
	return child[LEFT];
}

template <typename T1, typename T2>
typename map<T1, T2>::Node *
map<T1, T2>::Node::left(void) const
{
	return child[LEFT];
}

template <typename T1, typename T2>
typename map<T1, T2>::Node *
map<T1, T2>::Node::get_child() const
{
	if (this->left())
		return this->left();
	return this->right();
}

template <typename T1, typename T2>
typename map<T1, T2>::Node *
map<T1, T2>::Node::get_grandparent() const
{
	if (this->parent)
		return this->parent->parent;
	return 0;
}

template <typename T1, typename T2>
typename map<T1, T2>::Node *
map<T1, T2>::Node::get_uncle() const
{
	Node *grandParent(this->get_grandparent());

	if (grandParent == 0)
		return 0;
	if (grandParent->left() == this->parent)
		return grandParent->right();
	return grandParent->left();
}

template <typename T1, typename T2>
typename map<T1, T2>::Node *
map<T1, T2>::Node::get_sibling() const
{
	enum e_side side(this->get_side());
	if (side == LEFT)
		side = RIGHT;
	else
		side = LEFT;

	return this->parent->child[side];
}

template <typename T1, typename T2>
typename map<T1, T2>::Node *
map<T1, T2>::Node::get_predecessor() const
{
	Node *predecessor(this->left());

	while (predecessor->right())
		predecessor = predecessor->right();

	return predecessor;
}

template <typename T1, typename T2>
typename map<T1, T2>::e_side
map<T1, T2>::Node::get_side() const
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

template <typename T1, typename T2>
T1 &
map<T1, T2>::Node::key(void)
{
	return dual.first;
}

template <typename T1, typename T2>
T1
map<T1, T2>::Node::key(void) const
{
	return dual.first;
}
