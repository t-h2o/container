#include	"color.hpp"

template <typename T>
class	Vector
{
	public:
		Vector(void);
		~Vector(void);

		void	assign(unsigned int, T);

	private:
		int		*_list;
};

#include "../templates/Vector.cpp"
