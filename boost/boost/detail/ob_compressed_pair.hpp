//  (C) Copyright Steve Cleary, Beman Dawes, Howard Hinnant & John Maddock 2000.
//  Permission to copy, use, modify, sell and
//  distribute this software is granted provided this copyright notice appears
//  in all copies. This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.

//  See http://www.boost.org for most recent version including documentation.
//  see libs/utility/compressed_pair.hpp
//
/* Release notes:
   03 Oct 2000:
      Added VC6 support (JM).
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
#if defined(BOOST_MSVC6_MEMBER_TEMPLATES) || !defined(BOOST_NO_MEMBER_TEMPLATES)
//
// use member templates to emulate
// partial specialisation:
//
namespace detail{

template <class T1, class T2>
class compressed_pair_0
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

            compressed_pair_0() : _first(), _second() {}
            compressed_pair_0(first_param_type x, second_param_type y) : _first(x), _second(y) {}
   explicit compressed_pair_0(first_param_type x) : _first(x), _second() {}

   first_reference       first()       { return _first; }
   first_const_reference first() const { return _first; }

   second_reference       second()       { return _second; }
   second_const_reference second() const { return _second; }

   void swap(compressed_pair_0& y)
   {
      using std::swap;
      swap(_first, y._first);
      swap(_second, y._second);
   }
};

template <class T1, class T2>
class compressed_pair_1 : T2
{
private:
   T1 _first;
public:
   typedef T1                                                 first_type;
   typedef T2                                                 second_type;
   typedef typename call_traits<first_type>::param_type       first_param_type;
   typedef typename call_traits<second_type>::param_type      second_param_type;
   typedef typename call_traits<first_type>::reference        first_reference;
   typedef typename call_traits<second_type>::reference       second_reference;
   typedef typename call_traits<first_type>::const_reference  first_const_reference;
   typedef typename call_traits<second_type>::const_reference second_const_reference;

            compressed_pair_1() : T2(), _first() {}
            compressed_pair_1(first_param_type x, second_param_type y) : T2(y), _first(x) {}
   explicit compressed_pair_1(first_param_type x) : T2(), _first(x) {}

   first_reference       first()       { return _first; }
   first_const_reference first() const { return _first; }

   second_reference       second()       { return *this; }
   second_const_reference second() const { return *this; }

   void swap(compressed_pair_1& y)
   {
      // no need to swap empty base class:
      using std::swap;
      swap(_first, y._first);
   }
};

template <class T1, class T2>
class compressed_pair_2 : T1
{
private:
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

            compressed_pair_2() : T1(), _second() {}
            compressed_pair_2(first_param_type x, second_param_type y) : T1(x), _second(y) {}
   explicit compressed_pair_2(first_param_type x) : T1(x), _second() {}

   first_reference       first()       { return *this; }
   first_const_reference first() const { return *this; }

   second_reference       second()       { return _second; }
   second_const_reference second() const { return _second; }

   void swap(compressed_pair_2& y)
   {
      // no need to swap empty base class:
      using std::swap;
      swap(_second, y._second);
   }
};

template <class T1, class T2>
class compressed_pair_3 : T1, T2
{
public:
   typedef T1                                                 first_type;
   typedef T2                                                 second_type;
   typedef typename call_traits<first_type>::param_type       first_param_type;
   typedef typename call_traits<second_type>::param_type      second_param_type;
   typedef typename call_traits<first_type>::reference        first_reference;
   typedef typename call_traits<second_type>::reference       second_reference;
   typedef typename call_traits<first_type>::const_reference  first_const_reference;
   typedef typename call_traits<second_type>::const_reference second_const_reference;

            compressed_pair_3() : T1(), T2() {}
            compressed_pair_3(first_param_type x, second_param_type y) : T1(x), T2(y) {}
   explicit compressed_pair_3(first_param_type x) : T1(x), T2() {}

   first_reference       first()       { return *this; }
   first_const_reference first() const { return *this; }

   second_reference       second()       { return *this; }
   second_const_reference second() const { return *this; }

   void swap(compressed_pair_3& y)
   {
      // no need to swap empty base classes:
   }
};

// T1 == T2, and empty
template <class T1, class T2>
class compressed_pair_4 : T1
{
public:
   typedef T1                                                 first_type;
   typedef T2                                                 second_type;
   typedef typename call_traits<first_type>::param_type       first_param_type;
   typedef typename call_traits<second_type>::param_type      second_param_type;
   typedef typename call_traits<first_type>::reference        first_reference;
   typedef typename call_traits<second_type>::reference       second_reference;
   typedef typename call_traits<first_type>::const_reference  first_const_reference;
   typedef typename call_traits<second_type>::const_reference second_const_reference;

            compressed_pair_4() : T1() {}
            compressed_pair_4(first_param_type x, second_param_type) : T1(x) {}
   explicit compressed_pair_4(first_param_type x) : T1(x) {}

   first_reference       first()       { return *this; }
   first_const_reference first() const { return *this; }

   second_reference       second()       { return *this; }
   second_const_reference second() const { return *this; }

   void swap(compressed_pair_4& y)
   {
      // no need to swap empty base classes:
   }
};

// T1 == T2, not empty
template <class T1, class T2>
class compressed_pair_5
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

            compressed_pair_5() : _first(), _second() {}
            compressed_pair_5(first_param_type x, second_param_type y) : _first(x), _second(y) {}
   explicit compressed_pair_5(first_param_type x) : _first(x), _second() {}

   first_reference       first()       { return _first; }
   first_const_reference first() const { return _first; }

   second_reference       second()       { return _second; }
   second_const_reference second() const { return _second; }

   void swap(compressed_pair_5& y)
   {
      using std::swap;
      swap(_first, y._first);
      swap(_second, y._second);
   }
};

template <bool e1, bool e2, bool same>
struct compressed_pair_chooser
{
   template <class T1, class T2>
   struct rebind
   {
      typedef compressed_pair_0<T1, T2> type;
   };
};

template <>
struct compressed_pair_chooser<false, true, false>
{
   template <class T1, class T2>
   struct rebind
   {
      typedef compressed_pair_1<T1, T2> type;
   };
};

template <>
struct compressed_pair_chooser<true, false, false>
{
   template <class T1, class T2>
   struct rebind
   {
      typedef compressed_pair_2<T1, T2> type;
   };
};

template <>
struct compressed_pair_chooser<true, true, false>
{
   template <class T1, class T2>
   struct rebind
   {
      typedef compressed_pair_3<T1, T2> type;
   };
};

template <>
struct compressed_pair_chooser<true, true, true>
{
   template <class T1, class T2>
   struct rebind
   {
      typedef compressed_pair_4<T1, T2> type;
   };
};

template <>
struct compressed_pair_chooser<false, false, true>
{
   template <class T1, class T2>
   struct rebind
   {
      typedef compressed_pair_5<T1, T2> type;
   };
};

template <class T1, class T2>
struct compressed_pair_traits
{
private:
   typedef compressed_pair_chooser<is_empty<T1>::value, is_empty<T2>::value, is_same<T1,T2>::value> chooser;
   typedef typename chooser::template rebind<T1, T2> bound_type;
public:
   typedef typename bound_type::type type;
};

} // namespace detail

template <class T1, class T2>
class compressed_pair : public detail::compressed_pair_traits<T1, T2>::type
{
private:
   typedef typename detail::compressed_pair_traits<T1, T2>::type base_type;
public:
   typedef T1                                                 first_type;
   typedef T2                                                 second_type;
   typedef typename call_traits<first_type>::param_type       first_param_type;
   typedef typename call_traits<second_type>::param_type      second_param_type;
   typedef typename call_traits<first_type>::reference        first_reference;
   typedef typename call_traits<second_type>::reference       second_reference;
   typedef typename call_traits<first_type>::const_reference  first_const_reference;
   typedef typename call_traits<second_type>::const_reference second_const_reference;

            compressed_pair() : base_type() {}
            compressed_pair(first_param_type x, second_param_type y) : base_type(x, y) {}
   explicit compressed_pair(first_param_type x) : base_type(x) {}
   // can't define this in case T1 == T2:
   // explicit compressed_pair(second_param_type y) : _first(), _second(y) {}

   first_reference       first()       { return base_type::first(); }
   first_const_reference first() const { return base_type::first(); }

   second_reference       second()       { return base_type::second(); }
   second_const_reference second() const { return base_type::second(); }
};

template <class T1, class T2>
inline void swap(compressed_pair<T1, T2>& x, compressed_pair<T1, T2>& y)
{
   x.swap(y);
}

#else
// no partial specialisation, no member templates:

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

#endif

} // boost

#endif // BOOST_OB_COMPRESSED_PAIR_HPP

