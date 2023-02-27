#ifndef NODE_HPP
#define NODE_HPP

namespace ft
{

enum e_side
{
	LEFT,
	RIGHT
};

enum e_side _flip_side(enum e_side);

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

template <typename value_type> class Node
{
  public:
	typedef value_type	  TYPE;
	typedef Node		 *node_pointer;
	typedef node_pointer &node_pointer_reference;

	Node(Node *);
	Node	  *parent;
	Node	  *child[2];
	value_type dual;
	Color	   color;

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

	node_pointer_reference right();
	node_pointer		   right() const;
	node_pointer_reference left();
	node_pointer		   left() const;

	node_pointer get_child() const;
	node_pointer get_grandparent() const;
	node_pointer get_uncle() const;
	node_pointer get_sibling() const;
	node_pointer get_predecessor() const;

	enum e_side get_side() const;

	TYPE &key();
	TYPE  key() const;
};

#include "../templates/Color.cpp"
#include "../templates/Node.cpp"

} /* namespace ft */

#endif /* NODE_HPP */
