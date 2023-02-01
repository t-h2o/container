#include "Iterator.hpp"
#include "color.hpp"
#include "random_access_iterator.hpp"
#include "test.hpp"

namespace ft
{

class asdf : iterator<random_access_iterator_tag, int>
{
  public:
	value_type a;
};

}

int
main(void)
{
	title("Main");

	test_vector();

	std::iterator_traits<int *> traits;

	ft::asdf ss;

	ss.a = 12;

	int tint[2];

	ft::random_access_iterator rai(tint);

	(void)ss;
	(void)traits;

	return 0;
}
