template <typename T1, typename T2> map<T1, T2>::map(void) : _root(0), _size(0)
{
	_end = new Node(0);
	_root = new Node *;
	*_root = 0;
}

template <typename T1, typename T2> map<T1, T2>::~map(void)
{
	_free_tree(*_root);
	delete _end;
	delete _root;
}

/**
 * Iterator
 */

template <typename T1, typename T2>
typename map<T1, T2>::iterator
map<T1, T2>::begin(void) const
{
	Node *less(*_root);

	while (less->left())
		less = less->left();

	return iterator(_root, less, _end);
}

template <typename T1, typename T2>
typename map<T1, T2>::iterator
map<T1, T2>::end(void) const
{
	return iterator(_root, _end);
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

	Node *node(_binary_search(key));

	if (node == 0 || node->key() != key)
		return;

	_erase(node);

	if (RBT_CHECKER)
		_rbt_checker();
}

/**
 * Operations
 */

template <typename T1, typename T2>
typename map<T1, T2>::iterator
map<T1, T2>::find(T1 const &key) const
{
	Node *node(_binary_search(key));

	if (node->key() == key)
		return iterator(_root, node, _end);
	return iterator(_root, _end);
}

template <typename T1, typename T2>
size_t
map<T1, T2>::count(T1 const &key) const
{
	Node *node(_binary_search(key));

	if (node->key() == key)
		return 1;
	return 0;
}

/**
 * Extra
 */

template <typename T1, typename T2>
void
map<T1, T2>::print_tree(void) const
{
	_print_tree(*_root, 0);
}

template <typename T1, typename T2>
void
map<T1, T2>::print(void) const
{
	Node *ptr(*_root);

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

/*
 *    P              N
 *   / \            / \
 *  /   \          /   \
 * S     N   =>   P     D
 *      / \      / \
 *     C   D    S   C
 */

template <typename T1, typename T2>
void
map<T1, T2>::_rotate_del(Node *node)
{
	enum e_side side(node->get_side());
	enum e_side oside(_flip_side(side));

	Node *parent(node->parent);
	Node *childc(node->child[oside]);

	if (RBT_LOG_ERASE)
		std::cout << "Rotate deletion: " << node->key() << std::endl;

	parent->child[side] = childc;
	node->child[oside] = parent;
	if (parent->parent)
	{
		parent->parent->child[parent->get_side()] = node;
		node->parent = parent->parent;
	}
	else
	{
		*_root = node;
		node->parent = 0;
	}
	parent->parent = node;
	if (childc)
		childc->parent = parent;

	if (RBT_LOG_ERASE)
		std::cout << "Rotate deletion: tree" << std::endl;
	if (RBT_LOG_ERASE)
		print_tree();
}

template <typename T1, typename T2>
int
map<T1, T2>::_case_0(Node *node, bool deletion)
{
	if (node->is_red() && node->is_leaf())
	{
		if (RBT_LOG_ERASE)
			std::cout << "Case 0: node: " << node->key() << " is red & leaf" << std::endl;

		if (!deletion)
			return 1;
		node->parent->child[node->get_side()] = 0;
		delete node;
		--_size;
		return 1;
	}
	return 0;
}

template <typename T1, typename T2>
int
map<T1, T2>::_case_1(Node *node, Node *sibling, bool deletion)
{
	if (node->is_black() && sibling->is_red())
	{
		if (RBT_LOG_ERASE)
			std::cout << "Case 1: node is black; sibling is red;" << std::endl;

		sibling->set_black();
		node->parent->set_red();

		_rotate_del(sibling);

		if (deletion)
		{
			_erase(node);
			return 1;
		}
		_solve(node, false);

		return 1;
	}
	return 0;
}

template <typename T1, typename T2>
int
map<T1, T2>::_case_2(Node *node, Node *sibling, bool deletion)
{
	if (node->is_black() && sibling->is_black() && sibling->has_black_children())
	{
		if (RBT_LOG_ERASE)
			std::cout << "Case 2: node is black; sibling is black; sibling has two black children"
					  << std::endl;

		sibling->set_red();
		Node *nodeP(node->parent);

		if (deletion)
		{
			if (RBT_LOG_ERASE)
				std::cout << "Case 2: delete: " << node->key() << std::endl;
			node->parent->child[node->get_side()] = 0;
			delete node;
			--_size;
		}

		if (nodeP->is_red())
		{
			nodeP->set_black();
			return 1;
		}
		if (*_root == nodeP)
			return 1;

		_solve(nodeP, false);
		return 1;
	}
	return 0;
}

template <typename T1, typename T2>
int
map<T1, T2>::_case_3(Node *node, Node *sibling, bool deletion)
{
	enum e_side side(node->get_side());
	enum e_side oside(_flip_side(side));

	if (node->is_black() && sibling->is_black() && sibling->child[side] && sibling->child[side]->is_red()
		&& (!sibling->child[oside] || sibling->child[oside]->is_black()))
	{
		if (RBT_LOG_ERASE)
			std::cout << "Case 3: node is black; sibling is black; nephew side is red; nephew oside is black"
					  << std::endl;

		if (sibling->child[side])
			sibling->child[side]->set_black();
		sibling->set_red();
		_rotate_del(sibling->child[side]);
		_case_4(node, node->parent->child[oside], deletion);

		return 1;
	}
	return 0;
}

template <typename T1, typename T2>
int
map<T1, T2>::_case_4(Node *node, Node *sibling, bool deletion)
{
	enum e_side side(node->get_side());
	enum e_side oside(_flip_side(side));

	if (node->is_black() && sibling->is_black() && sibling->child[oside] && sibling->child[oside]->is_red())
	{
		if (RBT_LOG_ERASE)
			std::cout << "Case 4: node is black; sibling is black; nephew side is black; nephew oside is red"
					  << std::endl;

		sibling->color = node->parent->color;
		node->parent->set_black();
		sibling->child[oside]->set_black();
		_rotate_del(sibling);

		if (!deletion)
			return 1;
		node->parent->child[side] = 0;
		delete node;
		--_size;

		return 1;
	}
	return 0;
}

template <typename T1, typename T2>
void
map<T1, T2>::_solve(Node *node, bool deletion)
{
	if (RBT_LOG_ERASE)
		std::cout << "_solve(" << node->key() << ", " << deletion << ")" << std::endl;
	if (RBT_LOG_ERASE)
		print_tree();

	if (_case_0(node, deletion))
		return;

	Node *sibling(node->get_sibling());
	if (sibling)
	{
		if (_case_1(node, sibling, deletion))
			return;
		if (_case_2(node, sibling, deletion))
			return;
		if (_case_3(node, sibling, deletion))
			return;
		if (_case_4(node, sibling, deletion))
			return;
	}

	return;
}

template <typename T1, typename T2>
void
map<T1, T2>::_erase(Node *node)
{
	if (node == 0)
	{
		if (RBT_LOG_ERASE)
			std::cout << "_erase(NULL POINTER)" << std::endl;
		return;
	}

	if (RBT_LOG_ERASE)
		std::cout << "_erase(" << node->key() << ")" << std::endl;
	if (RBT_LOG_ERASE)
		print_tree();

	if (_size == 1)
	{
		if (RBT_LOG_ERASE)
			std::cout << "_erase: node is alone and the root" << std::endl;

		delete node;
		--_size;
		*_root = 0;
		return;
	}

	if (node->number_child() == 2)
	{
		if (RBT_LOG_ERASE)
			std::cout << "_erase: node has two children: find a predecessor" << std::endl;
		Node *predecessor(node->get_predecessor());

		_swap(node, predecessor);
		_erase(node);
		return;
	}
	else if (node->number_child() == 1)
	{
		if (RBT_LOG_ERASE)
			std::cout << "_erase: node has one child: swap with its child" << std::endl;
		Node *child(node->get_child());

		_swap(node, child);
	}

	_solve(node, true);
	return;
}

template <typename T1, typename T2>
pair<T1, T2> &
map<T1, T2>::_get_reference(const T1 &key)
{
	Node	   *parent;
	Node	   *node;
	enum e_side side;

	parent = _binary_search(key);
	if (parent)
	{
		if (parent->key() == key)
			return parent->dual;
		else if (parent->key() > key)
			side = LEFT;
		else if (parent->key() < key)
			side = RIGHT;
	}

	node = _new_node(parent, side);

	++_size;

	node->key() = key;

	_rebalance_tree(node);

	if (RBT_LOG)
		section("print_tree()");
	if (RBT_LOG)
		print_tree();

	if (RBT_CHECKER)
		_rbt_checker();

	return node->dual;
}

/**
 *  @brief  Print the tree (Ascii art).
 *  @param  The parent pointer, the level indentation.
 *
 *  It's a recursive function for printing left child, parent and right child.
 */
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

	if (ptr->is_red())
		std::cout << COL_RED;
	else
		std::cout << COL_YEL;

	std::cout << ptr->dual << std::endl << COL_RES;

	_print_tree(ptr->left(), level + 1);
}

/**
 *  @brief  Free the entire tree.
 *  @param  The parent pointer to free.
 *
 *  It's a recursive function for freeing children first and parent second.
 */
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

/**
 *  @brief  Search into a binary tree.
 *  @param  The value to search.
 *
 *  Search the value into a binary tree.
 *  If the value is equal to a node, return a pointer on the node,
 *  else return a pointer on the parent for this value.
 */
template <typename T1, typename T2>
typename map<T1, T2>::Node *
map<T1, T2>::_binary_search(T1 const &key) const
{
	Node *parent;

	parent = *_root;
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

	node = new Node(parent);

	if (parent)
		parent->child[side] = node;
	else
		*_root = node;

	return node;
}

template <typename T1, typename T2>
void
map<T1, T2>::_swap(Node *one, Node *two)
{
	Node	   *onechild[2]{ one->child[0], one->child[1] };
	Node	   *oneparent(one->parent);
	enum e_side oneside;
	if (one != *_root)
		oneside = one->get_side();
	Color onecolor(one->color);

	Node	   *twochild[2]{ two->child[0], two->child[1] };
	Node	   *twoparent(two->parent);
	enum e_side twoside;
	if (two != *_root)
		twoside = two->get_side();
	Color twocolor(two->color);

	if (RBT_LOG)
		std::cout << "Swap one: " << one->key() << " with two: " << two->key() << std::endl;

	if (onechild[0] == two || onechild[1] == two)
	{
		if (RBT_LOG)
			std::cout << "two is a child of one" << std::endl;

		// Swap parent of one's children
		if (onechild[0])
			onechild[0]->parent = two;
		if (onechild[1])
			onechild[1]->parent = two;

		// Swap parent of two's children
		if (twochild[0])
			twochild[0]->parent = one;
		if (twochild[1])
			twochild[1]->parent = one;

		one->left() = twochild[LEFT];
		one->right() = twochild[RIGHT];

		two->left() = onechild[LEFT];
		two->right() = onechild[RIGHT];
		two->child[twoside] = one;
		if (*_root == one)
		{
			*_root = two;
			two->parent = 0;
		}
		else
		{
			two->parent = one->parent;
			oneparent->child[oneside] = two;
		}
		one->parent = two;
		one->color = twocolor;
		two->color = onecolor;
	}
	else if (twochild[0] == one || twochild[1] == one)
	{
		if (RBT_LOG)
			std::cout << "one is a child of two" << std::endl;
	}
	else
	{
		if (RBT_LOG)
			std::cout << "one and two aren't parent<->child" << std::endl;

		// Swap parent of one's children
		if (onechild[0])
			onechild[0]->parent = two;
		if (onechild[1])
			onechild[1]->parent = two;

		// Swap parent of two's children
		if (twochild[0])
			twochild[0]->parent = one;
		if (twochild[1])
			twochild[1]->parent = one;

		// swap one children;
		one->left() = twochild[LEFT];
		one->right() = twochild[RIGHT];

		// swap two children;
		two->left() = onechild[LEFT];
		two->right() = onechild[RIGHT];

		// swap one parent
		one->parent = twoparent;

		// swap two parent
		two->parent = oneparent;

		if (*_root == one)
		{
			*_root = two;
			twoparent->child[twoside] = one;
		}
		else if (*_root == two)
		{
			*_root = one;
			oneparent->child[oneside] = two;
		}
		else
		{
			twoparent->child[twoside] = one;
			oneparent->child[oneside] = two;
		}
		one->color = twocolor;
		two->color = onecolor;
	}

	if (RBT_LOG)
		std::cout << "after swap" << std::endl;
	if (RBT_LOG)
		print_tree();
}

template <typename T1, typename T2>
void
map<T1, T2>::_rebalance_tree(Node *node)
{
	if (node == 0)
		return;

	if (RBT_LOG)
		std::cout << " == Red black tree rebalance == with " << node->key() << " as node" << std::endl;
	if (RBT_LOG)
		print_tree();

	if (node == *_root)
	{
		node->set_black();
		return;
	}

	if (node->is_black() || node->parent->is_black())
		return;

	Node *grandParent(node->get_grandparent());
	Node *uncle(node->get_uncle());

	if (uncle && uncle->is_red())
	{
		if (RBT_LOG)
			std::cout << "uncle is red" << std::endl;
		grandParent->color_children_black();
		grandParent->set_red();
		_rebalance_tree(grandParent);
		return;
	}

	Node *sibling(node->get_sibling());

	if (sibling == 0)
	{
		if (RBT_LOG)
			std::cout << "node hasn't sibling" << std::endl;
		_rebalance_tree(_rotate(node->parent));
		return;
	}

	if (sibling->is_black())
	{
		if (RBT_LOG)
			std::cout << "node has a black sibling" << std::endl;
		_rebalance_tree(_rotate(node->parent));
		return;
	}
}

template <typename T1, typename T2>
typename map<T1, T2>::Node *
map<T1, T2>::_rotate(Node *pivot)
{
	Node	   *root(pivot->parent);
	enum e_side side(pivot->get_side());
	enum e_side oSide(_flip_side(side));

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
			*_root = pivot;
		else
		{
			root->parent->child[root->get_side()] = pivot;
		}
		root->parent = pivot;
		if (root->child[side])
			root->child[side]->parent = root;
		pivot->color_children_red();
		pivot->set_black();
		return pivot;
	}
	return 0;
}

/**
 * Side
 */

template <typename T1, typename T2>
typename map<T1, T2>::e_side
map<T1, T2>::_flip_side(enum e_side side) const
{
	if (side == LEFT)
		return RIGHT;
	else
		return LEFT;
}
