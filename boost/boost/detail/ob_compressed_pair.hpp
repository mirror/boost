//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version including documentation.
//
/* Release notes:
   23rd July 2000:
      Additional comments added. (JM)
   Jan 2000:
      Original version: this version crippled for use with crippled compilers
      - John Maddock Jan 2000.
*/


#ifndef BOOST_OB_COMPRESSED_PAIR_HPP
#define BOOST_OB_COMPRESSED_PAIR_HPP

#include <algorithm>
#ifndef BOOST_TYPE_TRAITS_HPP
#include <boost/type_traits.hpp>
#endif
#ifndef BOOST_CALL_TRAITS_HPP
#include <boost/call_traits.hpp>
#endif

namespace boost
{

template <class T1, class T2>
class compressed_pair
{
private:
   T1 _first;
   T2 _second;
public:
   typedef T1                                                 first_type;
   typedef T2                                                 second_type;
   typedef typename call_traits<first_type>::param_type       first_param_type;
   typedef typename call_traits<second_type>::param_type      second_param_type;
   typedef typename call_traits<first_type>::reference        first_reference;
   typedef typename call_traits<second_type>::reference       second_reference;
   typedef typename call_traits<first_type>::const_reference  first_const_reference;
   typedef typename call_traits<second_type>::const_reference second_const_reference;

            compressed_pair() : _first(), _second() {}
            compressed_pair(first_param_type x, second_param_type y) : _first(x), _second(y) {}
   explicit compressed_pair(first_param_type x) : _first(x), _second() {}
   // can't define this in case T1 == T2:
   // explicit compressed_pair(second_param_type y) : _first(), _second(y) {}

   first_reference       first()       { return _first; }
   first_const_reference first() const { return _first; }

   second_reference       second()       { return _second; }
   second_const_reference second() const { return _second; }

   void swap(compressed_pair& y)
   {
      using std::swap;
      swap(_first, y._first);
      swap(_second, y._second);
   }
};

template <class T1, class T2>
inline void swap(compressed_pair<T1, T2>& x, compressed_pair<T1, T2>& y)
{
   x.swap(y);
}

} // boost

#endif // BOOST_OB_COMPRESSED_PAIR_HPP

