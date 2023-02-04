#ifndef MAP_HPP
#define MAP_HPP

#define RBT_LOG 0
#define RBT_LOG_ERASE 0
#define RBT_LOG_CHECKER 0

#define RBT_CHECKER 0

#include "Pair.hpp"

namespace ft
{

// template < class Key,  map::key_type class T,  map::mapped_type class Compare = less<Key>, map::key_compare
// class Alloc = allocator<pair<const Key,T> >  map::allocator_type > class map;

template <typename Key, typename Type, typename Alloc = std::allocator<ft::pair<Key, Type> > > class map
{
	enum e_side
	{
		LEFT,
		RIGHT
	};

	typedef Alloc allocator_type;

	typedef typename allocator_type::pointer		 pointer;
	typedef typename allocator_type::reference		 reference;
	typedef typename allocator_type::const_pointer	 const_pointer;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::difference_type difference_type;
	typedef typename allocator_type::size_type		 size_type;

	typedef ft::pair<Key, Type> pair;

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

		Key &key();
		Key	 key() const;
	};

  public:
	explicit map(void);
	~map(void);

	/* Capacity */
	bool   empty(void) const;
	size_t size(void) const;

	/* Element access */
	pair &operator[](const Key &);

	/* Modifiers */
	void insert(pair const &);
	void erase(Key const &);

	void print(void) const;
	void print_tree(void) const;

  private:
	Node **_root;
	size_t _size;

	void _free_tree(Node *);
	void _print_tree(Node *, size_t) const;

	Node *_binary_search(Key const &) const;
	Node *_new_node(Node *, enum e_side &);
	Node *_get_pointer(Key const &) const;
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

	pair &_get_reference(const Key &);
};

#include "../templates/Color.cpp"
#include "../templates/Map.cpp"
#include "../templates/Node.cpp"
#include "../templates/RBTchecker.cpp"

} /* namespace ft */

#endif /* MAP_HPP */
