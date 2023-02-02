template <typename T>
void
Tdd::expected(T const &a, T const &b)
{
	if (a == b)
		return;
	std::cout << "a: " << a << std::endl << "b: " << b << std::endl;
};
