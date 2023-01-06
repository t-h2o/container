#ifndef MAP_HPP
#define MAP_HPP

#include "Pair.hpp"

#define LEFT 0
#define RIGHT 1

namespace ft
{

template <typename T1, typename T2> class map
{
	typedef ft::pair<T1, T2> pair;

	typedef struct s_node
	{
		struct s_node *child[2];
		pair		   dual;
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

  private:
	t_node *_root;
	size_t	_size;

	void _free_tree(void);
};

#include "../templates/Map.cpp"

} /* namespace ft */

#endif /* MAP_HPP */
