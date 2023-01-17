#ifndef MAP_HPP
#define MAP_HPP

#define RBT_LOG 0
#define RBT_LOG_ERASE 1

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

	typedef struct s_node
	{
		struct s_node *parent;
		struct s_node *child[2];
		pair		   dual;
		enum e_color   color;
	} t_node;

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
	t_node *_root;
	size_t	_size;

	void _free_tree(t_node *);
	void _print_tree(t_node *, size_t) const;

	t_node *_get_parent(T1 const &, enum e_side &) const;
	t_node *_new_node(t_node *, enum e_side &);
	t_node *_get_grandparent(t_node *) const;
	t_node *_get_uncle(t_node *) const;
	t_node *_get_pointer(T1 const &) const;

	void _rebalanceTree(t_node *);
	void _flip_color(t_node *);
	void _flip_color_grandparent(t_node *);
	void _flip_side(enum e_side &);
	void _rotate(t_node *);
	void _erase(T1 const &);

	enum e_side _get_side(t_node *);

	unsigned char _number_child(t_node *) const;

	pair &_get_reference(const T1 &);

	bool _is_leaf(t_node *) const;
};

#include "../templates/Map.cpp"

} /* namespace ft */

#endif /* MAP_HPP */
