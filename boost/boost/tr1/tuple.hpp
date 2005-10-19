//  (C) Copyright John Maddock 2005.
//  Use, modification and distribution are subject to the
//  Boost Software License, Version 1.0. (See accompanying file
//  LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef BOOST_TR1_TUPLE_HPP_INCLUDED
#  define BOOST_TR1_TUPLE_HPP_INCLUDED
#  include <boost/tr1/detail/config.hpp>

#ifdef BOOST_HAS_TR1_TUPLE

#  include <BOOST_TR1_HEADER(tuple)>

#else

#include <boost/tuple/tuple.hpp>
#include <boost/tuple/tuple_comparison.hpp>
#include <boost/type_traits/integral_constant.hpp>

namespace std{ namespace tr1{

using ::boost::tuple;

// [6.1.3.2] Tuple creation functions
using ::boost::tuples::ignore;
using ::boost::make_tuple;
using ::boost::tie;

// [6.1.3.3] Tuple helper classes
template <class T> 
struct tuple_size 
   : public ::boost::integral_constant
   < ::std::size_t, ::boost::tuples::length<T>::value>
{};

template < int I, class T>
struct tuple_element
{
   typedef typename boost::tuples::element<I,T>::type type;
};

#if !BOOST_WORKAROUND(__BORLANDC__, BOOST_TESTED_AT(0x570))
// [6.1.3.4] Element access
using ::boost::get;
#endif

} } // namespaces

#endif

#endif
