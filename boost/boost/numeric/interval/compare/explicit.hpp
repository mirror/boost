#ifndef BOOST_NUMERIC_INTERVAL_COMPARE_EXPLICIT_HPP
#define BOOST_NUMERIC_INTERVAL_COMPARE_EXPLICIT_HPP

#include <boost/numeric/interval/detail/interval_prototype.hpp>

namespace boost {
namespace numeric {
namespace interval_lib {

/*
 * Certainly... operations
 */

template<class T, class Policies1, class Policies2> inline
bool cerlt(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() < y.lower();
}

template<class T, class Policies> inline
bool cerlt(const interval<T, Policies>& x, const T& y)
{
  return x.upper() < y;
}

template<class T, class Policies> inline
bool cerlt(const T& x, const interval<T, Policies>& y)
{
  return x < y.lower();
}

template<class T, class Policies1, class Policies2> inline
bool cerle(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() <= y.lower();
}

template<class T, class Policies> inline
bool cerle(const interval<T, Policies>& x, const T& y)
{
  return x.upper() <= y;
}

template<class T, class Policies> inline
bool cerle(const T& x, const interval<T, Policies>& y)
{
  return x <= y.lower();
}

template<class T, class Policies1, class Policies2> inline
bool cergt(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.lower() > y.upper();
}

template<class T, class Policies> inline
bool cergt(const interval<T, Policies>& x, const T& y)
{
  return x.lower() > y;
}

template<class T, class Policies> inline
bool cergt(const T& x, const interval<T, Policies>& y)
{
  return x > y.upper();
}

template<class T, class Policies1, class Policies2> inline
bool cerge(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.lower() >= y.upper();
}

template<class T, class Policies> inline
bool cerge(const interval<T, Policies>& x, const T& y)
{
  return x.lower() >= y;
}

template<class T, class Policies> inline
bool cerge(const T& x, const interval<T, Policies>& y)
{
  return x >= y.upper();
}

template<class T, class Policies1, class Policies2> inline
bool cereq(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.lower() == y.upper() && y.lower() == x.upper();
}

template<class T, class Policies> inline
bool cereq(const interval<T, Policies>& x, const T& y)
{
  return x.lower() == y && x.upper() == y;
}

template<class T, class Policies> inline
bool cereq(const T& x, const interval<T, Policies>& y)
{
  return x == y.lower() && x == y.upper();
}

template<class T, class Policies1, class Policies2> inline
bool cerne(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() < y.lower() || y.upper() < x.lower();
}

template<class T, class Policies> inline
bool cerne(const interval<T, Policies>& x, const T& y)
{
  return x.upper() < y || y < x.lower();
}

template<class T, class Policies> inline
bool cerne(const T& x, const interval<T, Policies>& y)
{
  return x < y.lower() || y.upper() < x;
}

/*
 * Possibly... comparisons
 */

template<class T, class Policies1, class Policies2> inline
bool poslt(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.lower() < y.upper();
}

template<class T, class Policies> inline
bool poslt(const interval<T, Policies>& x, const T& y)
{
  return x.lower() < y;
}

template<class T, class Policies> inline
bool poslt(const T& x, const interval<T, Policies>& y)
{
  return x < y.upper();
}

template<class T, class Policies1, class Policies2> inline
bool posle(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.lower() <= y.upper();
}

template<class T, class Policies> inline
bool posle(const interval<T, Policies>& x, const T& y)
{
  return x.lower() <= y;
}

template<class T, class Policies> inline
bool posle(const T& x, const interval<T, Policies>& y)
{
  return x <= y.upper();
}

template<class T, class Policies1, class Policies2> inline
bool posgt(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() > y.lower();
}

template<class T, class Policies> inline
bool posgt(const interval<T, Policies>& x, const T& y)
{
  return x.upper() > y;
}

template<class T, class Policies> inline
bool posgt(const T& x, const interval<T, Policies> & y)
{
  return x > y.lower();
}

template<class T, class Policies1, class Policies2> inline
bool posge(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() >= y.lower();
}

template<class T, class Policies> inline
bool posge(const interval<T, Policies>& x, const T& y)
{
  return x.upper() >= y;
}

template<class T, class Policies> inline
bool posge(const T& x, const interval<T, Policies>& y)
{
  return x >= y.lower();
}

template<class T, class Policies1, class Policies2> inline
bool poseq(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() >= y.lower() && y.upper() >= x.lower();
}

template<class T, class Policies> inline
bool poseq(const interval<T, Policies>& x, const T& y)
{
  return x.upper() >= y && y >= x.lower();
}

template<class T, class Policies> inline
bool poseq(const T& x, const interval<T, Policies>& y)
{
  return x >= y.lower() && y.upper() >= x;
}

template<class T, class Policies1, class Policies2> inline
bool posne(const interval<T, Policies1>& x, const interval<T, Policies2>& y)
{
  return x.upper() != y.lower() || y.upper() != x.lower();
}

template<class T, class Policies> inline
bool posne(const interval<T, Policies>& x, const T& y)
{
  return x.upper() != y || y != x.lower();
}

template<class T, class Policies> inline
bool posne(const T& x, const interval<T, Policies>& y)
{
  return x != y.lower() || y.upper() != x;
}

} // namespace interval_lib
} // namespace numeric
} //namespace boost

#endif // BOOST_NUMERIC_INTERVAL_COMPARE_EXPLICIT_HPP
