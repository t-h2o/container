#include "Pair.hpp"

namespace ft
{

template <typename T1, typename T2> class map
{
	typedef ft::pair<T1, T2> pair;

  public:
	explicit map(void);

  private:
	pair _root;
};

#include "../templates/Map.cpp"

} /* namespace ft */
