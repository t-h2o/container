#include "Tdd.hpp"
#include "color.hpp"
#include "test.hpp"

int
main(void)
{
	title("Main");

	Tdd::expected<int>(1, 2);
	test_vector();

	return 0;
}
