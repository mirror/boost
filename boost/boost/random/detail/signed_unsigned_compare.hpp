
#ifndef BOOST_RANDOM_DETAIL_SIGNED_UNSIGNED_COMPARE
#define BOOST_RANDOM_DETAIL_SIGNED_UNSIGNED_COMPARE

#include <boost/limits.hpp>

namespace boost {
namespace random {

/*
 * Correctly compare two numbers whose types possibly differ in signedness.
 * See boost::numeric_cast<> for the general idea.
 * Most "if" statements involve only compile-time constants, so the
 * optimizing compiler can do its job easily.
 */

template<class T1, class T2>
int equal_signed_unsigned(T1 x, T2 y)
{
  typedef std::numeric_limits<T1> x_traits;
  typedef std::numeric_limits<T2> y_traits;
  if(x_traits::is_signed == y_traits::is_signed) {
    // no difference in signedness, cast to the larger type
    if(x_traits::digits > y_traits::digits)
      return x == static_cast<T1>(y);
    else
      return static_cast<T2>(x) == y;
  } else if(x_traits::is_signed) {
    // y must be unsigned, i.e. non-negative
    if(x < 0)
      return false;
    else 
      return static_cast<T2>(x) == y;
  } else {          // !x_traits::is_signed && y_traits::is_signed
    // x must be unsigned, i.e. non-negative
    if(y < 0)
      return false;
    else
      return x == static_cast<T1>(y);
  }
}

template<class T1, class T2>
int lessthan_signed_unsigned(T1 x, T2 y)
{
  typedef std::numeric_limits<T1> x_traits;
  typedef std::numeric_limits<T2> y_traits;
  if(x_traits::is_signed == y_traits::is_signed) {
    // no difference in signedness, everything ok
    if(x_traits::digits > y_traits::digits)
      return x < static_cast<T1>(y);
    else
      return static_cast<T2>(x) < y;
  } else if(x_traits::is_signed) {
    // y must be unsigned, i.e. non-negative
    if(x < 0)
      return true;
    else 
      return static_cast<T2>(x) < y;
  } else {          // !x_traits::is_signed && y_traits::is_signed
    // x must be unsigned, i.e. non-negative
    if(y < 0)
      return false;
    else
      return x < static_cast<T1>(y);
  }
}

} // namespace random
} // namespace boost

#endif // BOOST_RANDOM_DETAIL_SIGNED_UNSIGNED_COMPARE
