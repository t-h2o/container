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

	_erase(key);
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

	if (_size == 1)
	{
		if (RBT_LOG_ERASE)
			std::cout << "node (" << node->dual.first << ") is alone and is the root" << std::endl;

		delete node;
		_root = 0;
		_size = 0;
		return;
	}
	if (_is_leaf(node))
	{
		if (node->color == RED)
		{
			if (RBT_LOG_ERASE)
				std::cout << "node (" << node->dual.first << ") is leaf and red" << std::endl;

			node->parent->child[_get_side(node)] = 0;
			delete node;
			_size--;
		}
		else if (node->color == BLACK)
		{
			if (RBT_LOG_ERASE)
				std::cout << "node (" << node->dual.first << ") is leaf and black" << std::endl;
		}
	}
	else if (_number_child(node) == 1)
	{
		t_node *child = _get_child(node);

		if (child->color == RED)
		{
			if (RBT_LOG_ERASE)
				std::cout << "node (" << node->dual.first << ") has one red child (" << child->dual.first
						  << ")" << std::endl;

			node->dual = child->dual;
			node->child[_get_side(child)] = 0;
			delete child;
			_size--;
		}
		else if (child->color == BLACK)
		{
			if (RBT_LOG_ERASE)
				std::cout << "node (" << node->dual.first << ") has one black child ()" << std::endl;
		}
	}
	else
	{
		if (RBT_LOG_ERASE)
			std::cout << "node (" << node->dual.first << ") has two children" << std::endl;
	}
}

template <typename T1, typename T2>
unsigned char
map<T1, T2>::_number_child(t_node *node) const
{
	return (!!(node->child[LEFT]) + !!(node->child[RIGHT]));
}

template <typename T1, typename T2>
typename map<T1, T2>::t_node *
map<T1, T2>::_get_child(t_node *node) const
{
	if (node->child[LEFT])
		return node->child[LEFT];
	return node->child[RIGHT];
}

template <typename T1, typename T2>
bool
map<T1, T2>::_is_leaf(t_node *node) const
{
	return !(node->child[LEFT] || node->child[RIGHT]);
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

	_rebalanceTree(node);

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
map<T1, T2>::_rebalanceTree(t_node *node)
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
					print_tree();
				if (RBT_LOG)
					std::cout << grandParent->dual.first << " => " << uncle->dual.first << " & "
							  << node->parent->dual.first << " -> " << node->dual.first << std::endl
							  << "uncle and parent are RED" << std::endl;

				_flip_color_grandparent(grandParent);
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

				_rotate(node->parent);
			}
		}
		else
		{
			if (RBT_LOG)
				std::cout << node->dual.first << " hasn't uncle" << std::endl;
			_rotate(node->parent);
		}
	}
}

template <typename T1, typename T2>
void
map<T1, T2>::_rotate(t_node *pivot)
{
	t_node	   *root(pivot->parent);
	enum e_side side(_get_side(pivot));
	enum e_side oSide = side;

	_flip_side(oSide);

	if (RBT_LOG)
		print_tree();

	if (RBT_LOG)
		std::cout << "pivot: " << pivot->dual.first << std::endl;

	if (pivot->child[LEFT] && pivot->child[RIGHT])
	{
		if (RBT_LOG)
			std::cout << "pivot has two child" << std::endl;
		if (RBT_LOG)
			std::cout << "pivot -> child oposite side: " << pivot->child[oSide]->dual.first << std::endl;

		root->child[side] = pivot->child[oSide];
		pivot->child[oSide] = root;
		if (root->parent == 0)
		{
			_root = pivot;
			pivot->parent = 0;
			root->parent = pivot;
		}
		else
		{
			root->parent->child[_get_side(root)] = pivot;
			pivot->parent = root->parent;
			root->parent = pivot;
		}
		pivot->color = BLACK;
		pivot->child[LEFT]->color = RED;
		pivot->child[RIGHT]->color = RED;
	}
	else if (pivot->child[oSide])
	{
		if (RBT_LOG)
			std::cout << "oposite side" << std::endl;

		std::cout << "pivot child oposite: " << pivot->child[oSide]->dual.first << std::endl;
		pivot->child[oSide]->child[side] = pivot;
		pivot->child[oSide]->child[oSide] = root;

		if (root->parent == 0)
		{
			if (RBT_LOG)
				std::cout << "is root" << std::endl;
			_root = pivot->child[oSide];
			pivot->child[oSide]->parent = 0;
			root->parent = pivot->child[oSide];
			pivot->parent = pivot->child[oSide];
			pivot->child[oSide]->color = BLACK;
		}
		else
		{
			if (RBT_LOG)
				std::cout << "isn't root" << std::endl;
			root->parent->child[_get_side(root)] = pivot->child[oSide];
			pivot->child[oSide]->parent = root->parent;
			root->parent = pivot->child[oSide];
			pivot->parent = pivot->child[oSide];
			pivot->child[oSide]->color = RED;
		}

		pivot->color = BLACK;
		root->color = BLACK;

		root->child[RIGHT] = 0;
		root->child[LEFT] = 0;
		pivot->child[RIGHT] = 0;
		pivot->child[LEFT] = 0;
	}
	else
	{
		if (RBT_LOG)
			std::cout << "same side" << std::endl;
		pivot->child[oSide] = root;
		if (root->parent == 0)
		{
			_root = pivot;
			pivot->parent = 0;
			root->parent = pivot;
		}
		else
		{
			root->parent->child[_get_side(root)] = pivot;
			pivot->parent = root->parent;
			root->parent = pivot;
		}
		root->child[side] = 0;
		pivot->color = BLACK;
		pivot->child[LEFT]->color = RED;
		pivot->child[RIGHT]->color = RED;
	}
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
map<T1, T2>::_flip_color_grandparent(t_node *grandParent)
{
	_flip_color(grandParent->child[LEFT]);
	_flip_color(grandParent->child[RIGHT]);
	if (grandParent->parent)
		_flip_color(grandParent);
	else
	{
		if (RBT_LOG)
			std::cout << "Grand parent (" << grandParent->dual.first << ") is the root" << std::endl;
		grandParent->color = BLACK;
	}
}
