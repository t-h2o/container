template <typename T1, typename T2> map<T1, T2>::map(void) : _root(0), _size(0) {}

template <typename T1, typename T2> map<T1, T2>::~map(void) { _free_tree(_root); }

/**
 * Capacity
 */

template <typename T1, typename T2>
bool
map<T1, T2>::empty(void) const
{
	return !_size;
}

template <typename T1, typename T2>
size_t
map<T1, T2>::size(void) const
{
	return _size;
}

template <typename T1, typename T2>
pair<T1, T2> &
map<T1, T2>::operator[](const T1 &key)
{
	return _get_reference(key);
}

/**
 * Modifiers
 */

template <typename T1, typename T2>
void
map<T1, T2>::insert(pair const &pair)
{
	_get_reference(pair.first).second = pair.second;
}

template <typename T1, typename T2>
void
map<T1, T2>::erase(T1 const &key)
{
	if (RBT_LOG_ERASE)
		print_tree();

	_erase(_get_pointer(key));
	if (RBT_CHECKER)
		_rbt_checker();
}

template <typename T1, typename T2>
void
map<T1, T2>::print_tree(void) const
{
	_print_tree(_root, 0);
}

template <typename T1, typename T2>
void
map<T1, T2>::print(void) const
{
	Node *ptr(_root);

	std::cout << "map: size = " << _size << std::endl;

	while (ptr)
	{
		std::cout << ptr->dual;
		ptr = ptr->left();
	}
}

/**
 * Private
 */

template <typename T1, typename T2>
void
map<T1, T2>::_erase(Node *node)
{
	if (node == 0)
		return;

	if (_size == 1)
	{
		if (RBT_LOG_ERASE)
			std::cout << "node (" << node->key() << ") is alone and is the root" << std::endl;

		delete node;
		_root = 0;
		_size = 0;
		return;
	}
	if (node->is_leaf())
	{
		if (node->color.is_red())
		{
			if (RBT_LOG_ERASE)
				std::cout << "node (" << node->key() << ") is leaf and red" << std::endl;

			node->parent->child[_get_side(node)] = 0;
			delete node;
			_size--;
		}
		else if (node->color.is_black())
		{
			if (RBT_LOG_ERASE)
				std::cout << "node (" << node->key() << ") is leaf and black" << std::endl;

			Node *sibling(_get_sibling(node));

			if (RBT_LOG_ERASE)
				std::cout << "node (" << node->key() << ") and his sibling(" << sibling->key() << ")"
						  << std::endl;

			if (RBT_LOG_ERASE)
				std::cout << "_resolve_double_black(" << sibling->key() << ", " << node->parent->key() << ")"
						  << std::endl;

			node->parent->child[_get_side(node)] = 0;

			_resolve_double_black(sibling, node->parent);

			delete node;
			--_size;
		}
	}
	else if (_number_child(node) == 1)
	{
		Node *child = _get_child(node);

		if (child->color.is_red())
		{
			if (RBT_LOG_ERASE)
				std::cout << "node (" << node->key() << ") has one red child (" << child->key() << ")"
						  << std::endl;

			node->dual = child->dual;
			node->child[_get_side(child)] = 0;
			delete child;
			_size--;
		}
		else if (child->color.is_black())
		{
			if (RBT_LOG_ERASE)
				std::cout << "node (" << node->key() << ") has one black child ()" << std::endl;
		}
	}
	else
	{
		if (RBT_LOG_ERASE)
			std::cout << "node (" << node->key() << ") has two children" << std::endl;

		Node *predecessor(_get_predecessor(node));

		if (RBT_LOG_ERASE)
			std::cout << "copy :" << predecessor->key() << " into " << node->key() << std::endl;

		node->dual = predecessor->dual;

		if (RBT_LOG_ERASE)
			std::cout << "_erase(" << predecessor->key() << ");" << std::endl;

		_erase(predecessor);
	}
}

template <typename T1, typename T2>
void
map<T1, T2>::_resolve_double_black(Node *sibling, Node *parent)
{
	if (RBT_LOG_ERASE)
		print_tree();

	if (sibling->color.is_black() && _has_black_children(sibling))
	{
		if (RBT_LOG_ERASE)
			std::cout << "sibling is black and has two black children" << std::endl;

		if (RBT_LOG_ERASE)
			std::cout << "color red sibling; color black parent" << std::endl;
		sibling->color.set_red();

		if (parent->color.is_black())
		{
			if (RBT_LOG_ERASE)
				std::cout << "parent is already black, so parent become double-black" << std::endl;

			if (parent->parent != 0)
			{
				if (RBT_LOG_ERASE)
					std::cout << "parent isn't root" << std::endl;

				sibling = _get_sibling(parent);
				parent = sibling->parent;
				if (RBT_LOG_ERASE)
					std::cout << "_resolve_double_black(" << sibling->key() << ", " << parent->key() << ")"
							  << std::endl;

				_resolve_double_black(sibling, parent);
			}
			else
			{
				if (RBT_LOG_ERASE)
					std::cout << "parent is root => end" << std::endl;
			}
			parent->color.set_black();
		}
		else if (parent->color.is_red())
		{
			if (RBT_LOG_ERASE)
				std::cout << "parent is red, so parent become black" << std::endl;

			parent->color.set_black();
		}
	}
	else if (sibling->color.is_black() && _has_red_child(sibling))
	{
		if (RBT_LOG_ERASE)
			std::cout << "sibling is black and has red child" << std::endl;
		if (RBT_LOG_ERASE)
			std::cout << "_rotate(" << sibling->key() << ")" << std::endl;

		_rotate(sibling);
	}
}

template <typename T1, typename T2>
bool
map<T1, T2>::_has_black_children(Node *node) const
{
	return ((!(node->left()) || node->left()->color.is_black())
			&& (!(node->right()) || node->right()->color.is_black()));
}

template <typename T1, typename T2>
bool
map<T1, T2>::_has_red_child(Node *node) const
{
	return ((node->left() && node->left()->color.is_red())
			|| (node->right() && node->right()->color.is_red()));
}

template <typename T1, typename T2>
unsigned char
map<T1, T2>::_number_child(Node *node) const
{
	return (!!(node->left()) + !!(node->right()));
}

template <typename T1, typename T2>
typename map<T1, T2>::Node *
map<T1, T2>::_get_sibling(Node *node) const
{
	return node->parent->child[_flip_side_s(_get_side(node))];
}

template <typename T1, typename T2>
typename map<T1, T2>::Node *
map<T1, T2>::_get_predecessor(Node *node) const
{
	Node *predecessor(node->left());

	while (predecessor->right())
		predecessor = predecessor->right();

	return predecessor;
}

template <typename T1, typename T2>
typename map<T1, T2>::Node *
map<T1, T2>::_get_child(Node *node) const
{
	if (node->left())
		return node->left();
	return node->right();
}

template <typename T1, typename T2>
typename map<T1, T2>::Node *
map<T1, T2>::_get_pointer(const T1 &key) const
{
	Node *node(_root);

	while (node && node->key() != key)
	{
		if (node->key() < key)
			node = node->right();
		else
			node = node->left();
	}
	if (node && node->key() == key)
		return node;
	return 0;
}

template <typename T1, typename T2>
pair<T1, T2> &
map<T1, T2>::_get_reference(const T1 &key)
{
	Node	   *parent;
	Node	   *node;
	enum e_side side;

	parent = _get_parent(key, side);
	if (parent && parent->key() == key)
		return parent->dual;

	node = _new_node(parent, side);

	++_size;

	node->key() = key;

	_rebalanceTree(node);

	if (RBT_LOG)
		section("print_tree()");
	if (RBT_LOG)
		print_tree();

	if (RBT_CHECKER)
		_rbt_checker();

	return node->dual;
}

template <typename T1, typename T2>
void
map<T1, T2>::_print_tree(Node *ptr, size_t level) const
{
	if (ptr == 0)
		return;

	_print_tree(ptr->right(), level + 1);

	std::cout << std::endl;

	for (size_t i = 0; i < level; ++i)
		std::cout << "    ";

	if (ptr->color.is_red())
		std::cout << COL_RED;
	else
		std::cout << COL_YEL;

	std::cout << ptr->dual << std::endl << COL_RES;

	_print_tree(ptr->left(), level + 1);
}

template <typename T1, typename T2>
void
map<T1, T2>::_free_tree(Node *ptr)
{
	if (ptr == 0)
		return;

	_free_tree(ptr->left());
	_free_tree(ptr->right());
	delete ptr;
}

template <typename T1, typename T2>
typename map<T1, T2>::Node *
map<T1, T2>::_get_parent(T1 const &key, enum e_side &side) const
{
	Node *parent;

	parent = _root;
	while (parent)
	{
		if (key > parent->key())
		{
			if (RBT_LOG)
				std::cout << key << " > " << parent->key() << " => Right" << std::endl;
			if (parent->right() == 0)
			{
				if (RBT_LOG)
					std::cout << key << " will be the right child of " << parent->key() << std::endl;
				side = RIGHT;
				break;
			}
			parent = parent->right();
		}
		else if (key < parent->key())
		{
			if (RBT_LOG)
				std::cout << key << " < " << parent->key() << " => Left" << std::endl;
			if (parent->left() == 0)
			{
				if (RBT_LOG)
					std::cout << key << " will be the left child of " << parent->key() << std::endl;
				side = LEFT;
				break;
			}
			parent = parent->left();
		}
		else if (key == parent->key())
		{
			if (RBT_LOG)
				std::cout << key << " = " << parent->key() << " => find the same key" << std::endl;
			return parent;
		}
	}
	return parent;
}

template <typename T1, typename T2>
typename map<T1, T2>::Node *
map<T1, T2>::_new_node(Node *parent, enum e_side &side)
{
	Node *node;

	if (parent == 0)
	{
		if (RBT_LOG)
			std::cout << "_root is NULL" << std::endl;
		node = new Node;
		node->color.set_black();
		node->parent = 0;
		_root = node;
	}
	else
	{
		node = new Node;
		parent->child[side] = node;
		node->color.set_red();
		node->parent = parent;
	}
	node->left() = 0;
	node->right() = 0;
	return node;
}

template <typename T1, typename T2>
typename map<T1, T2>::Node *
map<T1, T2>::_get_uncle(Node *node) const
{
	Node *grandParent(node->get_grandparent());

	if (grandParent == 0)
		return 0;
	if (grandParent->left() == node->parent)
		return grandParent->right();
	return grandParent->left();
}

template <typename T1, typename T2>
void
map<T1, T2>::_rebalanceTree(Node *node)
{
	if (node == 0)
		return;

	if (RBT_LOG)
		std::cout << " == Red black tree rebalance == with " << node->key() << " as node" << std::endl;
	if (RBT_LOG)
		print_tree();

	if (node == _root)
	{
		node->color.set_black();
		return;
	}

	if (node->is_black() || node->parent->is_black())
		return;

	Node *grandParent(node->get_grandparent());
	Node *uncle(_get_uncle(node));

	if (uncle && uncle->is_red())
	{
		if (RBT_LOG)
			std::cout << "uncle is red" << std::endl;
		grandParent->color_children_black();
		grandParent->color.set_red();
		_rebalanceTree(grandParent);
		return;
	}

	Node *sibling(_get_sibling(node));

	if (sibling == 0)
	{
		if (RBT_LOG)
			std::cout << "node hasn't sibling" << std::endl;
		_rebalanceTree(_rotate(node->parent));
		return;
	}

	if (sibling->is_black())
	{
		if (RBT_LOG)
			std::cout << "node has a black sibling" << std::endl;
		_rebalanceTree(_rotate(node->parent));
		return;
	}
}

template <typename T1, typename T2>
typename map<T1, T2>::Node *
map<T1, T2>::_rotate(Node *pivot)
{
	Node	   *root(pivot->parent);
	enum e_side side(_get_side(pivot));
	enum e_side oSide(_flip_side_s(side));

	if (RBT_LOG)
		std::cout << " == Red black tree rotate == with " << pivot->key() << " as pivot" << std::endl;
	if (RBT_LOG)
		print_tree();

	if (pivot->child[oSide] && pivot->child[oSide]->is_red())
	{
		if (RBT_LOG)
			std::cout << "opposite side" << std::endl;

		root->child[side] = pivot->child[oSide];

		pivot->child[oSide] = root->child[side]->child[side];
		if (pivot->child[oSide])
			pivot->child[oSide]->parent = pivot;
		root->child[side]->child[side] = pivot;

		pivot->parent = root->child[side];
		root->child[side]->parent = root;

		_rotate(root->child[side]);
	}
	else if (pivot->child[side] && pivot->child[side]->is_red())
	{
		if (RBT_LOG)
			std::cout << "same side" << std::endl;

		root->child[side] = pivot->child[oSide];
		pivot->child[oSide] = root;
		pivot->parent = root->parent;
		if (pivot->parent == 0)
			_root = pivot;
		else
		{
			root->parent->child[_get_side(root)] = pivot;
		}
		root->parent = pivot;
		if (root->child[side])
			root->child[side]->parent = root;
		pivot->color_children_red();
		pivot->color.set_black();
		return pivot;
	}
	return 0;
}

template <typename T1, typename T2>
typename map<T1, T2>::e_side
map<T1, T2>::_flip_side_s(enum e_side side) const
{
	if (side == LEFT)
		return RIGHT;
	else
		return LEFT;
}

template <typename T1, typename T2>
typename map<T1, T2>::e_side
map<T1, T2>::_get_side(Node *node) const
{
	if (node->parent == 0)
		std::cout << "Not a side" << std::endl;
	if (node->parent->right() == node)
	{
		if (RBT_LOG)
			std::cout << node->key() << " is right of " << node->parent->key() << std::endl;
		return RIGHT;
	}
	else if (node->parent->left() == node)
	{
		if (RBT_LOG)
			std::cout << node->key() << " is left of " << node->parent->key() << std::endl;
		return LEFT;
	}
	else
	{
		throw(std::logic_error("cannot get the child of the node"));
	}
}

template <typename T1, typename T2>
void
map<T1, T2>::_flip_color_grandparent(Node *grandParent)
{
	grandParent->left()->flip_color();
	grandParent->right()->flip_color();
	if (grandParent->parent)
		grandParent->flip_color();
	else
	{
		if (RBT_LOG)
			std::cout << "Grand parent (" << grandParent->key() << ") is the root" << std::endl;
		grandParent->color.set_black();
	}
}

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

/**
 * Node
 */

template <typename T1, typename T2>
void
map<T1, T2>::Node::flip_color(void)
{
	if (color.is_red())
		color.set_black();
	else
		color.set_red();
}

template <typename T1, typename T2>
void
map<T1, T2>::Node::color_children_red(void)
{
	if (left())
		left()->color.set_red();
	if (right())
		right()->color.set_red();
}

template <typename T1, typename T2>
void
map<T1, T2>::Node::color_children_black(void)
{
	if (left())
		left()->color.set_black();
	if (right())
		right()->color.set_black();
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
map<T1, T2>::Node::get_grandparent() const
{
	if (this->parent)
		return this->parent->parent;
	return 0;
}

template <typename T1, typename T2>
T1 &
map<T1, T2>::Node::key(void)
{
	return dual.first;
}

/**
 * Red black tree checker
 */

template <typename T1, typename T2>
void
map<T1, T2>::_rbt_checker(void) const
{
	Node		*node(_root);
	unsigned int black_node;
	unsigned int total_black_node;

	if (_root == 0)
		return;

	if (_root->color.is_red())
		throw(std::logic_error("Root is red"));

	if (RBT_LOG_CHECKER)
		std::cout << " == Red black tree checker ==" << std::endl;
	if (RBT_LOG_CHECKER)
		print_tree();

	black_node = 0;

	bool is_backing(0);
	bool reach_end(0);

	enum e_side side;
	while (true)
	{
		if (RBT_LOG_CHECKER)
			std::cout << node->key();
		if (node->is_black() && !is_backing)
			++black_node;
		if (node->right() && !is_backing)
		{
			if (RBT_LOG_CHECKER)
				std::cout << " -> ";
			if (node->is_red() && node->right()->is_red())
				throw(std::logic_error("two following red"));
			node = node->right();
			side = RIGHT;
			is_backing = 0;
		}
		else if (node->left() && (!is_backing || (is_backing && side == RIGHT)))
		{
			if (RBT_LOG_CHECKER)
				std::cout << " -> ";
			if (node->is_red() && node->left()->is_red())
				throw(std::logic_error("two following red"));
			node = node->left();
			side = LEFT;
			is_backing = 0;
		}
		else if (node->parent)
		{
			if (!reach_end && node->is_leaf())
			{
				reach_end = 1;
				total_black_node = black_node;
				if (RBT_LOG_CHECKER)
					std::cout << " : " << total_black_node << " black node" << std::endl;
			}
			else if (node->is_leaf())
			{
				if (RBT_LOG_CHECKER)
					std::cout << " : " << black_node << " black node" << std::endl;
				if (black_node != total_black_node)
					throw(std::logic_error("Not same number of black"));
			}
			else
			{
				if (RBT_LOG_CHECKER)
					std::cout << " <- ";
			}
			side = _get_side(node);
			if (node->is_black())
				--black_node;
			node = node->parent;
			is_backing = 1;
		}
		else
			break;
	}
	if (RBT_LOG_CHECKER)
		std::cout << std::endl;
}
