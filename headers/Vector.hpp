#include	"color.hpp"

template <typename T>
class	Vector
{
	public:
		Vector(void);
		~Vector(void);

		void	assign(unsigned int, T);

		unsigned int	size(void) const;
		unsigned int	max_size(void) const;
		bool			empty(void) const;

		T	&operator[](unsigned int) const;
		T	&front(void) const;
		T	&back(void) const;

	private:
		T				*_list;
		unsigned int	_maxSize;
		unsigned int	_size;
};

template <typename T>
std::ostream	&operator<<(std::ostream &output, Vector<T> const &);

#include "../templates/Vector.cpp"
