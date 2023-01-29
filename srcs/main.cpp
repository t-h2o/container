#include "Iterator.hpp"
#include "color.hpp"
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

	(void)ss;
	(void)traits;

	return 0;
}
