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

template <typename T> class vector
{
  public:
	typedef ft::random_access_iterator<T> iterator;

	/* Member Funcion */
	explicit vector(void);
	explicit vector(size_t, const T &);
	vector(iterator, iterator);
	vector(vector const &);
	~vector(void);
	vector &operator=(vector const &);

	/* Iterators */
	iterator begin(void);
	iterator end(void);

	/* Capacity */
	size_t size(void) const;
	size_t max_size(void) const;
	void   resize(size_t);
	size_t capacity(void) const;
	bool   empty(void) const;
	void   reserve(size_t);
	void   shrink_to_fit(void);

	/* Element access */
	T &operator[](size_t) const;
	T &at(size_t) const;
	T &front(void) const;
	T &back(void) const;
	T *data(void) const;

	/* Modifiers */
	void assign(size_t, T);
	void assign(iterator, iterator);
	void push_back(T const &);
	void pop_back(void);
	void insert(iterator, const T &);
	void insert(iterator, size_t, const T &);
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
	T	  *_list;
	size_t _size;
	size_t _allocated;

	std::allocator<T> _allocator;

	void _destroy_all(void);
	void _construct_value(const T &);
	void _construct_range(T *, iterator first, iterator last);
	void _first_allocation(size_t);

	size_t _new_size(size_t) const;

	T *_gen_new_list(size_t);
};

/* Extra... */
template <typename T> std::ostream &operator<<(std::ostream &output, vector<T> const &);

#include "../templates/Vector.cpp"

} /* namespace ft */
