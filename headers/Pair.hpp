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

  private:
	T1	  _first;
	T2	  _second;
};

#include "../templates/Pair.cpp"

} /* namespace ft */
