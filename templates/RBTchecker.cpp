/**
 * Red black tree checker
 */

template <typename Key, typename Type, typename Alloc>
void
map<Key, Type, Alloc>::_rbt_checker(void) const
{
	Node		*node(*_root);
	unsigned int black_node;
	unsigned int total_black_node;

	if (*_root == 0)
		return;

	if ((*_root)->is_red())
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
			side = node->get_side();
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
