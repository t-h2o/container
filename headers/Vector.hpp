#include	"color.hpp"

template <typename T>
class	Vector
{
	public:
		/* Member Funcion */
		Vector(void);
		~Vector(void);

		/* Capacity */
		unsigned int	size(void) const;
		unsigned int	max_size(void) const;
		bool			empty(void) const;

		/* Element access */
		T	&operator[](unsigned int) const;
		T	&at(unsigned int) const;
		T	&front(void) const;
		T	&back(void) const;

		/* Modifiers */
		void	assign(unsigned int, T);
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
		unsigned int	_maxSize;
		unsigned int	_size;
		unsigned int	_allocated;

		std::allocator<T>	_allocator;
};



/* Extra... */
template <typename T>
std::ostream	&operator<<(std::ostream &output, Vector<T> const &);

#include "../templates/Vector.cpp"
