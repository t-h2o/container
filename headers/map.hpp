#ifndef MAP_HPP
#define MAP_HPP

#define RBT_LOG 0
#define RBT_LOG_ERASE 0
#define RBT_LOG_CHECKER 0

#define RBT_CHECKER 0

#include "bidirectional_iterator.hpp"
#include "node.hpp"
#include "pair.hpp"

namespace ft
{

// template < class Key,  map::key_type class T,  map::mapped_type class Compare = less<Key>, map::key_compare
// class Alloc = allocator<pair<const Key,T> >  map::allocator_type > class map;

template <typename Key, typename Type, typename Alloc = std::allocator<ft::pair<Key, Type> > > class map
{

	typedef ft::pair<Key, Type> pair;
	typedef ft::Node<pair>		Node;
	typedef Alloc				allocator_type;

	typedef typename allocator_type::value_type		 value_type;
	typedef typename allocator_type::pointer		 pointer;
	typedef typename allocator_type::reference		 reference;
	typedef typename allocator_type::const_pointer	 const_pointer;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::difference_type difference_type;
	typedef typename allocator_type::size_type		 size_type;

  public:
	typedef ft::bidirectional_iterator<Node, pointer>		iterator;

	explicit map(void);
	~map(void);

	/* iterator */
	iterator begin() const;
	iterator end() const;

	/* Capacity */
	bool   empty(void) const;
	size_t size(void) const;

	/* Element access */
	reference operator[](const Key &);

	/* Modifiers */
	void insert(value_type const &);
	void erase(Key const &);

	void print(void) const;
	void print_tree(void) const;

  private:
	Node **_root;
	size_t _size;
	Node  *_end;

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

	reference _get_reference(const Key &);
};

#include "../templates/RBTchecker.cpp"
#include "../templates/map.cpp"

} /* namespace ft */

#endif /* MAP_HPP */
