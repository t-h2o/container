#include	"color.hpp"

template <typename T>
class	Vector
{
	public:
		/* Member Funcion */
		Vector(void);
		~Vector(void);

		/* Capacity */
		unsigned long	size(void) const;
		unsigned long	max_size(void) const;
		bool			empty(void) const;

		/* Element access */
		T	&operator[](unsigned long) const;
		T	&at(unsigned long) const;
		T	&front(void) const;
		T	&back(void) const;

		/* Modifiers */
		void	assign(unsigned long, T);
		void	push_back(T &);
		void	pop_back(void);

		class	out_of_range : public std::exception
		{
			public:
				const char *what() const throw()
				{
					return "Out of Range error: vector";
				}
		};

	private:
		T				*_list;
		unsigned long	_maxSize;
		unsigned long	_size;
		unsigned long	_allocated;

		std::allocator<T>	_allocator;
};



/* Extra... */
template <typename T>
std::ostream	&operator<<(std::ostream &output, Vector<T> const &);

#include "../templates/Vector.cpp"
