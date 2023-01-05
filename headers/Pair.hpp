namespace ft
{

template <typename T1, typename T2> class pair
{
  public:
	/* Member Funcion */
	pair(void);
	pair(const pair &);
	pair(T1 const &, const T2 &);

	pair &operator=(const pair &);

	void swap(pair &);

	T1	  first;
	T2	  second;
};

#include "../templates/Pair.cpp"

} /* namespace ft */
