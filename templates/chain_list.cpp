template <typename T, typename Alloc> chain_list<T, Alloc>::chain_list(void) : _start() {}

template <typename T, typename Alloc>
void
chain_list<T, Alloc>::put(const_reference item)
{
	std::cout << "Put: " << item << std::endl;
}
