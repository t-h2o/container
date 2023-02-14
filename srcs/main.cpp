#include "Tdd.hpp"
#include "color.hpp"
#include "test.hpp"

int
main(void)
{
	title("Main");

	Tdd::expected<int>(1, 2);
	test_vector();
	test_vector_2();
	test_pair();
	test_map();
	test_chain_list();
	test_random_access_iterator();
	test_rev_random_access_iterator();

	return 0;
}
