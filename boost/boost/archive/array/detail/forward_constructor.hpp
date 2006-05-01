#ifndef BOOST_ARCHIVE_ARRAY_DEATIL_FORWARD_CONSTRUCTOR_HPP
#define BOOST_ARCHIVE_ARRAY_DEATIL_FORWARD_CONSTRUCTOR_HPP

// (C) Copyright 2006 Matthias Troyer
// Use, modification and distribution is subject to the Boost Software
// License, Version 1.0. (See accompanying file LICENSE_1_0.txt or copy at
// http://www.boost.org/LICENSE_1_0.txt)


#include <boost/preprocessor/repetition.hpp>
#include <boost/preprocessor/empty.hpp>
#include <boost/preprocessor/punctuation/comma_if.hpp>
#include <boost/preprocessor/array/elem.hpp>
  
#ifndef BOOST_ARCHIVE_ARRAY_MAXARITY
#define BOOST_ARCHIVE_ARRAY_MAXARITY 3
#endif

#define BOOST_ARCHIVE_forward_constructor(z, n, args)                                 \
  template <class T BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, class T)>            \
  BOOST_PP_ARRAY_ELEM(0,args)(T BOOST_PP_ARRAY_ELEM(2,args) p BOOST_PP_COMMA_IF(n)    \
                              BOOST_PP_ENUM_BINARY_PARAMS(n, T, const& p) )           \
   : BOOST_PP_ARRAY_ELEM(1,args)(p BOOST_PP_COMMA_IF(n) BOOST_PP_ENUM_PARAMS(n, p) )  \
  {}

#define BOOST_ARCHIVE_FORWARD_CONSTRUCTOR(derived,base)                                                         \
  derived() : base() {}                                                                                         \
  BOOST_PP_REPEAT(BOOST_ARCHIVE_ARRAY_MAXARITY, BOOST_ARCHIVE_forward_constructor, (3,(derived, base, const&))) \
  BOOST_PP_REPEAT(BOOST_ARCHIVE_ARRAY_MAXARITY, BOOST_ARCHIVE_forward_constructor, (3,(derived, base, &)))     

#undef BOOST_ARCHIVE_DETAIL_forward_constructor

#endif // BOOST_ARCHIVE_ARRAY_DEATIL_FORWARD_CONSTRUCTOR_HPP
