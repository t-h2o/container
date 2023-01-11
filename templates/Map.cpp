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
	t_node *node = _get_pointer(key);

	if (_size == 1)
	{
		delete node;
		_root = 0;
		_size = 0;
		return;
	}
	else if (_size > 1)
	{
		_erase(key);
	}
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
map<T1, T2>::_erase(const T1 &key)
{
	t_node *node(_get_pointer(key));

	if (node == 0)
		return;

	if (_is_leaf(node))
	{
		node->parent->child[_get_side(node)] = 0;
		delete node;
		_size--;
	}
	else
	{
		t_node *largestLeft(node->child[LEFT]);

		while (largestLeft->child[RIGHT])
			largestLeft = largestLeft->child[RIGHT];

		node->dual = largestLeft->dual;
		delete node->child[LEFT];
		node->child[LEFT] = 0;

		// black sibling
		if (((!node->child[RIGHT]) || node->child[RIGHT]->color == BLACK)
			&& ((!node->child[LEFT]) || node->child[LEFT]->color == BLACK))
		{
			if (RBT_LOG)
				std::cout << "black sibling" << std::endl;
		}

		_size--;
	}
}

template <typename T1, typename T2>
bool
map<T1, T2>::_is_leaf(t_node *node) const
{
	return !(node->child[LEFT] && node->child[RIGHT]);
}

template <typename T1, typename T2>
typename map<T1, T2>::t_node *
map<T1, T2>::_get_pointer(const T1 &key) const
{
	t_node	   *parent;
	enum e_side side;

	parent = _get_parent(key, side);
	if (parent && parent->dual.first == key)
		return parent;
	return 0;
}

template <typename T1, typename T2>
pair<T1, T2> &
map<T1, T2>::_get_reference(const T1 &key)
{
	t_node	   *parent;
	t_node	   *node;
	enum e_side side;

	parent = _get_parent(key, side);
	if (parent && parent->dual.first == key)
		return parent->dual;

	node = _new_node(parent, side);

	++_size;

	node->dual.first = key;

	_check(node);

	if (RBT_LOG)
		section("print_tree()");
	if (RBT_LOG)
		print_tree();
	return node->dual;
}

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
			if (RBT_LOG)
				std::cout << key << " > " << parent->dual.first << " => Right" << std::endl;
			if (parent->child[RIGHT] == 0)
			{
				if (RBT_LOG)
					std::cout << key << " will be the right child of " << parent->dual.first << std::endl;
				side = RIGHT;
				break;
			}
			parent = parent->child[RIGHT];
		}
		else if (key < parent->dual.first)
		{
			if (RBT_LOG)
				std::cout << key << " < " << parent->dual.first << " => Left" << std::endl;
			if (parent->child[LEFT] == 0)
			{
				if (RBT_LOG)
					std::cout << key << " will be the left child of " << parent->dual.first << std::endl;
				side = LEFT;
				break;
			}
			parent = parent->child[LEFT];
		}
		else if (key == parent->dual.first)
		{
			if (RBT_LOG)
				std::cout << key << " = " << parent->dual.first << " => find the same key" << std::endl;
			return parent;
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
		if (RBT_LOG)
			std::cout << "_root is NULL" << std::endl;
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
	if (node && node->parent)
		return node->parent->parent;
	return 0;
}

template <typename T1, typename T2>
typename map<T1, T2>::t_node *
map<T1, T2>::_get_uncle(t_node *node) const
{
	t_node *grandParent(_get_grandparent(node));

	if (grandParent == 0)
		return 0;
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
			while (node->parent->color == RED && uncle->color == RED)
			{
				if (RBT_LOG)
					std::cout << "       node: " << node->dual.first << std::endl
							  << "grandParent: " << grandParent->dual.first << std::endl
							  << "      uncle: " << uncle->dual.first << std::endl
							  << "parent and uncle are RED" << std::endl
							  << "Before flip..." << std::endl;
				if (RBT_LOG)
					print_tree();

				_flip_color_grandparent(grandParent);

				if (RBT_LOG)
					std::cout << "after flip" << std::endl;
				if (RBT_LOG)
					print_tree();

				if (RBT_LOG)
					std::cout << "change node value: " << grandParent->dual.first << " <- "
							  << node->dual.first << std::endl;
				node = grandParent;
				grandParent = _get_grandparent(node);
				uncle = _get_uncle(node);
				if (grandParent == 0)
				{
					if (RBT_LOG)
						std::cout << "grandparent = 0" << std::endl;
					break;
				}
				if (node->parent == 0)
				{
					if (RBT_LOG)
						std::cout << "node->parent = 0" << std::endl;
					break;
				}
				if (uncle == 0)
				{
					if (RBT_LOG)
						std::cout << "uncle = 0" << std::endl;
					break;
				}
			}

			if (node->parent == 0)
				return;
			if (RBT_LOG)
				std::cout << "(end of while) parent: " << node->parent->dual.first << std::endl;
			if (node->color == RED && node->parent->color == RED)
			{
				if (RBT_LOG)
					std::cout << "node and parent are RED" << std::endl;
				t_node *root = _get_grandparent(node);
				t_node *parent = node->parent;

				if (RBT_LOG)
					std::cout << " root: " << root->dual.first << std::endl;
				if (RBT_LOG)
					std::cout << "pivot: " << parent->dual.first << std::endl;

				enum e_side os(_get_side(parent));
				enum e_side rs(os);
				_flip_side(rs);

				if (RBT_LOG)
					std::cout << "right" << std::endl;
				root->child[os] = parent->child[rs];
				root->child[os]->parent = root;
				parent->child[rs] = root;
				if (root->parent == 0)
				{
					_root = parent;
					parent->parent = 0;
				}
				else
				{
					root->parent->child[_get_side(root)] = parent;
					parent->parent = root->parent;
				}
				root->parent = parent;

				parent->child[LEFT]->color = RED;
				parent->child[RIGHT]->color = RED;
				parent->color = BLACK;
			}
		}
		else
		{
			if (RBT_LOG)
				std::cout << node->dual.first << " hasn't uncle" << std::endl;
			_rotate_two(node, node->parent);
		}
	}
}

template <typename T1, typename T2>
void
map<T1, T2>::_rotate_two(t_node *node, t_node *parent)
{
	if (RBT_LOG)
		print_tree();

	enum e_side node_side(_get_side(node));
	enum e_side parent_side(_get_side(parent));

	if (RBT_LOG)
		std::cout << std::endl;

	if (node_side == LEFT && parent_side == RIGHT)
	{
		if (RBT_LOG)
			std::cout << "rotate right " << std::endl;

		_rotate(node, RIGHT);

		_rotate_same_side(node->child[RIGHT], RIGHT, LEFT);
	}
	else if (node_side == RIGHT && parent_side == LEFT)
	{
		if (RBT_LOG)
			std::cout << "rotate left " << std::endl;

		_rotate(node, LEFT);

		_rotate_same_side(node->child[LEFT], LEFT, RIGHT);
	}
	else if (node_side == RIGHT && parent_side == RIGHT)
	{
		if (RBT_LOG)
			std::cout << "rotate right " << std::endl;

		_rotate_same_side(node, RIGHT, LEFT);
	}
	else if (node_side == LEFT && parent_side == LEFT)
	{
		if (RBT_LOG)
			std::cout << "rotate left " << std::endl;

		_rotate_same_side(node, LEFT, RIGHT);
	}
	else
	{
		if (RBT_LOG)
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
	{
		std::cout << "Flip " << node->dual.first << " RED -> BLACK" << std::endl;
		node->color = BLACK;
	}
	else
	{
		std::cout << "Flip " << node->dual.first << " BLACK -> RED" << std::endl;
		node->color = RED;
	}
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
	{
		if (RBT_LOG)
			std::cout << node->dual.first << " is right of " << node->parent->dual.first << std::endl;
		return RIGHT;
	}
	if (RBT_LOG)
		std::cout << node->dual.first << " is left of " << node->parent->dual.first << std::endl;
	return LEFT;
}

template <typename T1, typename T2>
void
map<T1, T2>::_rotate_same_side(t_node *node, enum e_side rs, enum e_side os)
{
	t_node *parent(node->parent);
	t_node *grandParent = _get_grandparent(node);

	if (RBT_LOG)
		print_tree();
	if (RBT_LOG)
		std::cout << grandParent->dual.first << " -> " << parent->dual.first << " -> " << node->dual.first
				  << std::endl;

	parent->child[os] = grandParent;
	if (grandParent->parent == 0)
	{
		_root = parent;
		parent->parent = 0;
	}
	else
	{
		grandParent->parent->child[_get_side(grandParent)] = parent;
		parent->parent = grandParent->parent;
	}
	grandParent->parent = parent;
	grandParent->child[os] = 0;
	grandParent->child[rs] = 0;
	parent->color = BLACK;
	parent->child[os]->color = RED;
	parent->child[rs]->color = RED;

	if (RBT_LOG)
		print_tree();
	if (RBT_LOG)
		std::cout << parent->dual.first << " => " << grandParent->dual.first << " & " << node->dual.first
				  << std::endl;
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
