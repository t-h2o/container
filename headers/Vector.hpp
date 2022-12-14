#include	"color.hpp"

class	Vector
{
	public:
		Vector(void);
		~Vector(void);

		void	assign(unsigned int, int);

	private:
		int		*_list;
};
