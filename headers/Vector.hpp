#include	"color.hpp"


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
template <typename T>
class	Vector
{
	public:
		/* Member Funcion */
		Vector(void);
		~Vector(void);
		Vector	&operator=(Vector const &);

		/* Capacity */
		size_t	size(void) const;
		size_t	max_size(void) const;
		bool	empty(void) const;

		/* Element access */
		T	&operator[](size_t) const;
		T	&at(size_t) const;
		T	&front(void) const;
		T	&back(void) const;

		/* Modifiers */
		void	assign(size_t, T);
		void	push_back(T const &);
		void	pop_back(void);
		void	clear(void);

		class	out_of_range : public std::exception
		{
			public:
				const char *what() const throw()
				{
					return "Out of Range error: vector";
				}
		};

	private:
		T		*_list;
		size_t	_maxSize;
		size_t	_size;
		size_t	_allocated;

		std::allocator<T>	_allocator;
};



/* Extra... */
template <typename T>
std::ostream	&operator<<(std::ostream &output, Vector<T> const &);

#include "../templates/Vector.cpp"
