/**
 *  @brief A standard container which offers fixed time access to
 *  individual elements in any order.
 *
 *  @ingroup sequences
 *
 *  @tparam T  Type of element.
 *
 *  In some terminology a %vector can be described as a dynamic
 *  C-style array, it offers fast and efficient access to individual
 *  elements in any order and saves the user from worrying about
 *  memory and size allocation.  Subscripting ( @c [] ) access is
 *  also provided as with C-style arrays.
 */

#include "random_access_iterator.hpp"

namespace ft
{

template <typename T, typename Alloc = std::allocator<T> > class vector
{
  public:
	typedef Alloc allocator_type;

	typedef typename allocator_type::pointer		 pointer;
	typedef typename allocator_type::reference		 reference;
	typedef typename allocator_type::const_pointer	 const_pointer;
	typedef typename allocator_type::const_reference const_reference;
	typedef typename allocator_type::difference_type difference_type;
	typedef typename allocator_type::size_type		 size_type;

	typedef ft::random_access_iterator<T> iterator;

	/* Member Funcion */
	explicit vector(void);
	explicit vector(size_type, const_reference);
	vector(iterator, iterator);
	vector(vector const &);
	~vector(void);
	vector &operator=(vector const &);

	/* Iterators */
	iterator begin(void);
	iterator end(void);

	/* Capacity */
	size_type size(void) const;
	size_type max_size(void) const;
	void	  resize(size_type);
	size_type capacity(void) const;
	bool	  empty(void) const;
	void	  reserve(size_type);
	void	  shrink_to_fit(void);

	/* Element access */
	reference operator[](size_type) const;
	reference at(size_type) const;
	reference front(void) const;
	reference back(void) const;
	pointer	  data(void) const;

	/* Modifiers */
	void assign(size_type, T);
	void assign(iterator, iterator);
	void push_back(T const &);
	void pop_back(void);
	void insert(iterator, const_reference);
	void insert(iterator, size_type, const_reference);
	void insert(iterator, iterator, iterator);
	void erase(iterator);
	void erase(iterator, iterator);
	void swap(vector &);
	void clear(void);

	class out_of_range : public std::exception
	{
	  public:
		const char *
		what() const throw()
		{
			return "Out of Range error: vector";
		}
	};

  private:
	pointer	  _list;
	size_type _size;
	size_type _allocated;

	allocator_type _allocator;

	void _destroy_all(void);
	void _construct_value(const_reference);
	void _construct_range(pointer, iterator first, iterator last);
	void _first_allocation(size_type);

	size_type _new_size(size_type) const;

	pointer _gen_new_list(size_type);
};

/* Extra... */
template <typename T> std::ostream &operator<<(std::ostream &output, vector<T> const &);

#include "../templates/Vector.cpp"

} /* namespace ft */
