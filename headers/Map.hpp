#ifndef MAP_HPP
#define MAP_HPP

#define RBT_LOG 0
#define RBT_LOG_ERASE 0
#define RBT_LOG_CHECKER 0

#define RBT_CHECKER 0

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

	typedef ft::pair<T1, T2> pair;

	class Color
	{
	  public:
		enum e_color
		{
			BLACK,
			RED
		};

		void flip();

		bool is_red() const;
		bool is_black() const;

		void set_red();
		void set_black();

	  private:
		enum e_color _color;
	};

	class Node
	{
	  public:
		Node(Node *);
		Node *parent;
		Node *child[2];
		pair  dual;
		Color color;

		void flip_color(void);
		void color_children_red();
		void color_children_black();
		void reset_parent(void);

		void set_black();
		void set_red();

		bool is_black() const;
		bool is_red() const;

		bool is_leaf() const;
		bool has_red_child() const;
		bool has_black_children() const;

		unsigned char number_child() const;

		Node *&right();
		Node  *right() const;
		Node *&left();
		Node  *left() const;

		Node *get_child() const;
		Node *get_grandparent() const;
		Node *get_uncle() const;
		Node *get_sibling() const;
		Node *get_predecessor() const;

		enum e_side get_side() const;

		T1 &key();
		T1	key() const;
	};

  public:
	class iterator
	{
	  public:
		iterator(void);
		iterator(Node *);

		pair &operator*(void);

		iterator &operator++(void);

	  private:
		Node *_actual;
	};

	explicit map(void);
	~map(void);

	/* Iterators */
	iterator begin() const;
	iterator end() const;

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

	Node *_binary_search(T1 const &) const;
	Node *_new_node(Node *, enum e_side &);
	Node *_get_pointer(T1 const &) const;
	Node *_rotate(Node *);

	void _rotate_del(Node *);
	void _solve(Node *, bool);

	int _case_0(Node *, bool);
	int _case_1(Node *, Node *, bool);
	int _case_2(Node *, Node *, bool);
	int _case_3(Node *, Node *, bool);
	int _case_4(Node *, Node *, bool);

	void _swap(Node *, Node *);
	void _rebalance_tree(Node *);
	void _erase(Node *);
	void _rbt_checker(void) const;

	enum e_side _flip_side(enum e_side) const;

	pair &_get_reference(const T1 &);
};

#include "../templates/Color.cpp"
#include "../templates/IteratorMap.cpp"
#include "../templates/Map.cpp"
#include "../templates/Node.cpp"
#include "../templates/RBTchecker.cpp"

} /* namespace ft */

#endif /* MAP_HPP */
