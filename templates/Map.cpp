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
	node->dual.first = key;

	_check(node);
	print_tree();
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
	node->child[LEFT] = 0;
	node->child[RIGHT] = 0;
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

		t_node *uncle(_get_uncle(node));
		t_node *grandParent(_get_grandparent(node));

		if (uncle != 0)
		{
			_flip_color_grandparent(grandParent);

			if (grandParent->color == RED && grandParent->parent
				&& grandParent->parent->color == RED)
			{
				t_node *root = grandParent->parent->parent;
				t_node *parent = grandParent->parent;

				print_tree();
				std::cout << "..." << std::endl;

				if (_get_side(parent) == RIGHT)
				{
					std::cout << "right" << std::endl;
					root->child[RIGHT] = parent->child[LEFT];
					root->child[RIGHT]->parent = root;
					parent->child[LEFT] = root;
					if (root->parent == 0)
					{
						_root = parent;
						parent->parent = 0;
					}
					root->parent = parent;

					parent->child[LEFT]->color = RED;
					parent->child[RIGHT]->color = RED;
					parent->color = BLACK;
				}
				else if (_get_side(parent) == LEFT)
				{
					std::cout << "left" << std::endl;
					root->child[LEFT] = parent->child[RIGHT];
					root->child[LEFT]->parent = root;
					parent->child[RIGHT] = root;
					if (root->parent == 0)
					{
						_root = parent;
						parent->parent = 0;
					}
					root->parent = parent;

					if (root->child[RIGHT]->color == RED)
					{
						root->child[RIGHT]->color = BLACK;
						root->child[RIGHT]->child[LEFT]->color = RED;
						root->child[RIGHT]->child[RIGHT]->color = RED;
					}
					parent->child[RIGHT]->color = RED;
					parent->child[LEFT]->color = RED;
					parent->color = BLACK;
				}
			}
		}
		else if (_get_side(node) == LEFT && _get_side(node->parent) == RIGHT)
		{
			_rotate(node, RIGHT);

			_rotate_same_side(node->child[RIGHT], RIGHT, LEFT);
		}
		else if (_get_side(node) == RIGHT && _get_side(node->parent) == RIGHT)
		{
			_rotate_same_side(node, RIGHT, LEFT);
		}
		else if (_get_side(node) == LEFT && _get_side(node->parent) == LEFT)
		{
			_rotate_same_side(node, LEFT, RIGHT);
		}
		else
			std::cout << "No case" << std::endl;
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

	if (parent->dual.first < node->dual.first)
		node->child[LEFT] = parent;
	else
		node->child[RIGHT] = parent;

	if (parent->dual.first < grandParent->dual.first)
		grandParent->child[LEFT] = node;
	else
		grandParent->child[RIGHT] = node;

	node->parent = grandParent;
	parent->child[LEFT] = 0;
	parent->child[RIGHT] = 0;
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

template <typename T1, typename T2>
typename map<T1, T2>::e_side
map<T1, T2>::_get_side(t_node *node)
{
	if (node->parent == 0)
		std::cout << "Not a side" << std::endl;
	if (node->parent->child[RIGHT] == node)
		return RIGHT;
	return LEFT;
}

template <typename T1, typename T2>
void
map<T1, T2>::_rotate_same_side(t_node *node, enum e_side rs, enum e_side os)
{
	t_node *parent(node->parent);
	t_node *grandParent = _get_grandparent(node);

	print_tree();
	std::cout << "rotate same side: " << rs << std::endl
			  << "  node: " << node->dual << std::endl
			  << "parent: " << parent->dual << std::endl
			  << " grand: " << grandParent->dual << std::endl;

	parent->child[os] = grandParent;
	if (grandParent->parent == 0)
	{
		_root = parent;
		parent->parent = 0;
	}
	else
	{
		grandParent->parent->child[_get_side(parent)] = parent;
		parent->parent = grandParent->parent;
	}
	grandParent->parent = parent;
	grandParent->child[os] = 0;
	grandParent->child[rs] = 0;
	parent->color = BLACK;
	parent->child[os]->color = RED;
	parent->child[rs]->color = RED;
}

template <typename T1, typename T2>
void
map<T1, T2>::_flip_color_grandparent(t_node *grandParent)
{
	_flip_color(grandParent->child[LEFT]);
	_flip_color(grandParent->child[RIGHT]);
	if (grandParent->parent)
		_flip_color(grandParent);
	else
		grandParent->color = BLACK;
}
