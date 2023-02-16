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
	typedef value_type TYPE;

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

	TYPE &key();
	TYPE  key() const;
};

#include "../templates/Color.cpp"
#include "../templates/Node.cpp"

} /* namespace ft */

#endif /* NODE_HPP */
