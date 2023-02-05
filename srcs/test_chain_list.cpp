#include "Tdd.hpp"
#include "color.hpp"
#include "test.hpp"

#include "chain_list.hpp"

void
test_chain_list(void)
{
	title("Chain list");

	ft::chain_list<int> a;
	a.last();
	a.put(42);
	a.last();
	a.put(1234);
	a.last();
}
