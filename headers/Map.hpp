#include "Pair.hpp"

namespace ft
{

template <typename T1, typename T2> class map
{
	typedef ft::pair<T1, T2> pair;

	typedef struct s_node
	{
		struct s_node *next;
		pair		   dual;
	} t_node;

  public:
	explicit map(void);
	~map(void);

  private:
	pair *_root;
};

#include "../templates/Map.cpp"

} /* namespace ft */
