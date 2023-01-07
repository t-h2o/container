#ifndef MAP_HPP
#define MAP_HPP

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

	void print(void) const;
	void print_tree(void) const;

  private:
	t_node *_root;
	size_t	_size;

	void	_free_tree(t_node *);
	void	_print_tree(t_node *, size_t) const;
	t_node *_get_parent(T1 const &, enum e_side &) const;
};

#include "../templates/Map.cpp"

} /* namespace ft */

#endif /* MAP_HPP */
