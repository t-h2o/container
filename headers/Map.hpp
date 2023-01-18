#ifndef MAP_HPP
#define MAP_HPP

#define RBT_LOG 0
#define RBT_LOG_ERASE 0

#define RBT_CHECKER 1

#include "Pair.hpp"

namespace ft
{

template <typename T1, typename T2> class map
{
	enum e_side
	{
		LEFT,
		RIGHT
	};

	enum e_color
	{
		BLACK,
		RED
	};

	typedef ft::pair<T1, T2> pair;

	class Node
	{
	  public:
		Node		*parent;
		Node		*child[2];
		pair		 dual;
		enum e_color color;

		void flip_color(void);
		void color_children(enum e_color);
		void reset_parent(void);

		bool is_leaf() const;
		bool is_black() const;
		bool is_red() const;
		bool has_red_child() const;

		Node *right() const;
		Node *left() const;

		T1 &key();
	};

  public:
	explicit map(void);
	~map(void);

	/* Capacity */
	bool   empty(void) const;
	size_t size(void) const;

	/* Element access */
	pair &operator[](const T1 &);

	/* Modifiers */
	void insert(pair const &);
	void erase(T1 const &);

	void print(void) const;
	void print_tree(void) const;

  private:
	Node  *_root;
	size_t _size;

	void _free_tree(Node *);
	void _print_tree(Node *, size_t) const;

	Node *_get_parent(T1 const &, enum e_side &) const;
	Node *_new_node(Node *, enum e_side &);
	Node *_get_grandparent(Node *) const;
	Node *_get_uncle(Node *) const;
	Node *_get_pointer(T1 const &) const;
	Node *_get_child(Node *) const;
	Node *_get_predecessor(Node *) const;
	Node *_get_sibling(Node *) const;

	void _rebalanceTree(Node *);
	void _flip_color(Node *);
	void _flip_color_grandparent(Node *);
	void _rotate(Node *);
	void _erase(Node *);
	void _resolve_double_black(Node *, Node *);
	void _rbt_checker(void) const;

	enum e_side _get_side(Node *) const;
	enum e_side _flip_side_s(enum e_side) const;

	unsigned char _number_child(Node *) const;

	pair &_get_reference(const T1 &);

	bool _has_black_children(Node *) const;
	bool _has_red_child(Node *) const;
};

#include "../templates/Map.cpp"

} /* namespace ft */

#endif /* MAP_HPP */
