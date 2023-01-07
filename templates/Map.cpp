template <typename T1, typename T2> map<T1, T2>::map(void) : _root(0), _size(0)
{
}

template <typename T1, typename T2> map<T1, T2>::~map(void)
{
	_free_tree(_root);
}

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
	t_node	   *parent;
	t_node	   *node;
	enum e_side side;

	parent = _get_parent(key, side);

	node = _new_node(parent, side);

	++_size;
	node->child[LEFT] = 0;
	node->child[RIGHT] = 0;
	node->dual.first = key;

	print_tree();
	_check(node);
	return node->dual;
}

/**
 * Modifiers
 */

template <typename T1, typename T2>
void
map<T1, T2>::insert(pair const &pair)
{
	t_node *ptr;

	ptr = _root;
	while (ptr && ptr->child[LEFT])
	{
		ptr = ptr->child[LEFT];
	}

	if (ptr)
	{
		ptr->child[LEFT] = new t_node;
		ptr = ptr->child[LEFT];
		ptr->color = RED;
	}
	else
	{
		ptr = new t_node;
		ptr->color = BLACK;
		_root = ptr;
	}
	++_size;

	ptr->child[LEFT] = 0;
	ptr->child[RIGHT] = 0;

	ptr->dual.first = pair.first;
	ptr->dual.second = pair.second;
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
	t_node *ptr(_root);

	std::cout << "map: size = " << _size << std::endl;

	while (ptr)
	{
		std::cout << ptr->dual;
		ptr = ptr->child[LEFT];
	}
}

/**
 * Private
 */

template <typename T1, typename T2>
void
map<T1, T2>::_print_tree(t_node *ptr, size_t level) const
{
	if (ptr == 0)
		return;

	_print_tree(ptr->child[RIGHT], level + 1);

	std::cout << std::endl;

	for (size_t i = 0; i < level; ++i)
		std::cout << "    ";

	if (ptr->color == RED)
		std::cout << COL_RED;
	else
		std::cout << COL_YEL;

	std::cout << ptr->dual << std::endl << COL_RES;

	_print_tree(ptr->child[LEFT], level + 1);
}

template <typename T1, typename T2>
void
map<T1, T2>::_free_tree(t_node *ptr)
{
	if (ptr == 0)
		return;

	_free_tree(ptr->child[LEFT]);
	_free_tree(ptr->child[RIGHT]);
	delete ptr;
}

template <typename T1, typename T2>
typename map<T1, T2>::t_node *
map<T1, T2>::_get_parent(T1 const &key, enum e_side &side) const
{
	t_node *parent;

	parent = _root;
	while (parent)
	{
		if (key > parent->dual.first)
		{
			if (parent->child[RIGHT] == 0)
			{
				side = RIGHT;
				break;
			}
			parent = parent->child[RIGHT];
		}
		else if (key < parent->dual.first)
		{
			if (parent->child[LEFT] == 0)
			{
				side = LEFT;
				break;
			}
			parent = parent->child[LEFT];
		}
	}
	return parent;
}

template <typename T1, typename T2>
typename map<T1, T2>::t_node *
map<T1, T2>::_new_node(t_node *parent, enum e_side &side)
{
	t_node *node;

	if (parent == 0)
	{
		node = new t_node;
		node->color = BLACK;
		node->parent = 0;
		_root = node;
	}
	else
	{
		node = new t_node;
		parent->child[side] = node;
		node->color = RED;
		node->parent = parent;
	}
	return node;
}

template <typename T1, typename T2>
typename map<T1, T2>::t_node *
map<T1, T2>::_get_grandparent(t_node *node) const
{
	return node->parent->parent;
}

template <typename T1, typename T2>
typename map<T1, T2>::t_node *
map<T1, T2>::_get_uncle(t_node *node) const
{
	t_node *grandParent(_get_grandparent(node));

	if (grandParent->child[LEFT] == node->parent)
		return grandParent->child[RIGHT];
	return grandParent->child[LEFT];
}

template <typename T1, typename T2>
void
map<T1, T2>::_check(t_node *node)
{
	// is two following red
	if (node->color == RED && node->parent && node->parent->color == RED)
	{
		std::cout << "two red" << std::endl;

		t_node *uncle(_get_uncle(node));
		t_node *grandParent(_get_grandparent(node));

		if (uncle != 0)
		{
			std::cout << "---- switch color ----" << std::endl;
			_flip_color(grandParent->child[LEFT]);
			_flip_color(grandParent->child[RIGHT]);
			if (grandParent->parent)
				_flip_color(grandParent);
			print_tree();
			return;
		}
		else
		{
			t_node *parent(node->parent);
			std::cout << "---- rotate ----" << std::endl
					  << "       node: " << node->dual << std::endl
					  << "     parent: " << parent->dual << std::endl
					  << "grandParent: " << grandParent->dual << std::endl;

			_rotate(node, RIGHT);

			print_tree();

			grandParent = _get_grandparent(node);
			parent = node->parent;
			std::cout << "---- rotate ----" << std::endl
					  << "       node: " << node->dual << std::endl
					  << "     parent: " << parent->dual << std::endl
					  << "grandParent: " << grandParent->dual << std::endl;

			node->child[LEFT] = parent;
			grandParent->child[RIGHT] = node;
			node->parent = grandParent;
			parent->child[RIGHT] = 0;
			parent->parent = node;

			print_tree();

			std::cout << "---- switch color ----" << std::endl;
			node->color = BLACK;
			node->child[LEFT]->color = RED;
			node->child[RIGHT]->color = RED;

			print_tree();
		}
	}
}

template <typename T1, typename T2>
void
map<T1, T2>::_rotate(t_node *node, enum e_side rs)
{
	enum e_side os(rs);
	_flip_side(os);

	t_node *parent(node->parent);
	t_node *grandParent(_get_grandparent(node));

	std::cout << "---- rotate ----" << std::endl
			  << "       node: " << node->dual << std::endl
			  << "     parent: " << parent->dual << std::endl
			  << "grandParent: " << grandParent->dual << std::endl;

	node->child[rs] = parent;
	grandParent->child[rs] = node;
	node->parent = grandParent;
	parent->child[os] = 0;
	parent->parent = node;
}

template <typename T1, typename T2>
void
map<T1, T2>::_flip_color(t_node *node)
{
	if (node == 0)
		return;
	if (node->color == RED)
		node->color = BLACK;
	else
		node->color = RED;
}

template <typename T1, typename T2>
void
map<T1, T2>::_flip_side(enum e_side &side)
{
	if (side == LEFT)
		side = RIGHT;
	else
		side = LEFT;
}
