namespace ft
{

template <typename T1, typename T2> class pair
{
  public:
	/* Member Funcion */
	explicit pair(T1 const &, const T2 &);

  private:
	T1	  _first;
	T2	  _second;
};

#include "../templates/Pair.cpp"

} /* namespace ft */
