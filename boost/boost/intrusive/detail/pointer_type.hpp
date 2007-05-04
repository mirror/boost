/////////////////////////////////////////////////////////////////////////////
//
// (C) Copyright Ion Gaztañaga 2006. Distributed under the Boost
// Software License, Version 1.0. (See accompanying file
// LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
// See http://www.boost.org/libs/intrusive for documentation.
//
/////////////////////////////////////////////////////////////////////////////

#ifndef BOOST_INTRUSIVE_POINTER_TYPE_HPP
#define BOOST_INTRUSIVE_POINTER_TYPE_HPP

#include <boost/intrusive/detail/config_begin.hpp>

namespace boost {
namespace intrusive {
namespace detail  {

struct two {char _[2];};

namespace pointer_type_imp
{

template <class U> static two  test(...);
template <class U> static char test(typename U::pointer* = 0);

}  //namespace pointer_type_imp

template <class T>
struct has_pointer_type
{
    static const bool value = sizeof(pointer_type_imp::test<T>(0)) == 1;
};

template <class T, class A, bool = has_pointer_type<A>::value>
struct pointer_type
{
    typedef typename A::pointer type;
};

template <class T, class A>
struct pointer_type<T, A, false>
{
    typedef T* type;
};

}  //namespace detail
}  //namespace intrusive
} // namespace boost

#include <boost/intrusive/detail/config_end.hpp>

#endif   //#ifndef BOOST_INTRUSIVE_POINTER_TYPE_HPP
