template <typename T1, typename T2> map<T1, T2>::map(void) : _root(0) {}

template <typename T1, typename T2> map<T1, T2>::~map(void) { delete _root; }
